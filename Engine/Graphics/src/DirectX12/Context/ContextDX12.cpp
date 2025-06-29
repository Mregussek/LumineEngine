
module;

#include "Types.h"
#include "LoggerDX12.h"
#include <wrl/client.h>
#include <d3d12.h>
#include <dxgi1_6.h>
#include <map>

module ContextDX12;

using Microsoft::WRL::ComPtr;

import GraphicsSpecification;
import SpecificationDX12;
import UtilitiesDX12;


namespace lumine::graphics::dx12
{

void ContextDX12::Create(const GraphicsSpecification& specs)
{
	DXTRACE("Creating");

	m_DxFactory.Create();
	m_DxDevice.Create(m_DxFactory.Adapter());

	m_DxCmdQueue.Create(m_DxDevice.Handle());

	m_DxSwapchain.Create(specs, m_DxFactory.Handle(), m_DxDevice.Handle(), m_DxCmdQueue.Handle());
	m_DxSwapchain.UpdateRTVs(m_DxDevice.Handle());

	m_pDxCmdAllocator.Create(m_DxDevice.Handle(), D3D12_COMMAND_LIST_TYPE_DIRECT);

	m_bCreated = true;
	DXDEBUG("Created");
}

void ContextDX12::Destroy()
{
	DXTRACE("Destroying");

	if (m_bCreated)
	{
		m_DxDevice.Destroy();
	}

	m_bCreated = false;
	DXDEBUG("Destroyed");
}


void DxFactoryDebug::Enable(UINT& dxgiFactoryFlags)
{
	DXTRACE("Enabling");

	ID3D12Debug6* pTmpDebug{ nullptr };

	HRESULT hr = D3D12GetDebugInterface(IID_PPV_ARGS(&pTmpDebug));
	DXASSERT(hr);

	hr = pTmpDebug->QueryInterface(IID_PPV_ARGS(&m_pHandle));
	DXASSERT(hr);

	m_pHandle->EnableDebugLayer();
	m_pHandle->SetEnableGPUBasedValidation(true);

	dxgiFactoryFlags |= DXGI_CREATE_FACTORY_DEBUG;

	pTmpDebug->Release();

	DXTRACE("Enabled Factory");
}


ComPtr<IDXGIAdapter4> DxAdapterSelector::Select(const ComPtr<IDXGIFactory7>& pFactoryHandle)
{
	IDXGIAdapter4* pAdapter;
	u32 adapterIndex = 0;

	std::multimap<u32, u32> ratings;
	while (pFactoryHandle->EnumAdapterByGpuPreference(adapterIndex, DXGI_GPU_PREFERENCE_UNSPECIFIED, IID_PPV_ARGS(&pAdapter)) != DXGI_ERROR_NOT_FOUND)
	{
		ratings.insert(std::make_pair(GetScore(pAdapter), adapterIndex));
		adapterIndex++;
	}

	u32 selectedAdapter = ratings.rbegin()->second;
	HRESULT hr = pFactoryHandle->EnumAdapterByGpuPreference(selectedAdapter, DXGI_GPU_PREFERENCE_UNSPECIFIED, IID_PPV_ARGS(&pAdapter));
	DXASSERT(hr);

	return pAdapter;
}


u32 DxAdapterSelector::GetScore(IDXGIAdapter4* pAdapter)
{
	u32 score{ 0 };

	DXGI_ADAPTER_DESC3 desc;
	pAdapter->GetDesc3(&desc);
	const std::string gpuName = GetGpuNameStr(desc);

	if (desc.Flags & DXGI_ADAPTER_FLAG3_SOFTWARE)
	{
		DXTRACE("Skipping software adapter {}; Score: {}", gpuName, score);
		return score;
	}

	bool bSupportsD3D12 = D3D12CreateDevice(pAdapter, L_D3D12_MIN_FEATURE_LEVEL, _uuidof(ID3D12Device), nullptr);
	if (not bSupportsD3D12)
	{
		DXTRACE("Skipping adapter {}, which does not support D3D12!", gpuName);
		return score;
	}

	u32 vramMb = static_cast<u32>(desc.DedicatedVideoMemory / 1024 / 1024);
	score += vramMb;

	DXTRACE("Adapter {}; VRAM {}; Score {}", gpuName, vramMb, score);
	return score;
}


void DxFactory::Create()
{
	DXTRACE("Creating");

	CreateFactory();
	SelectAdapter();

	DXDEBUG("Created");
}


void DxFactory::CreateFactory()
{
	UINT dxgiFactoryFlags{ 0 };

#if LUMINE_DEBUG
	m_DebugFactory.Enable(dxgiFactoryFlags);
#endif

	HRESULT hr = CreateDXGIFactory2(dxgiFactoryFlags, IID_PPV_ARGS(m_pFactory.ReleaseAndGetAddressOf()));
	DXASSERT(hr);
}


void DxFactory::SelectAdapter()
{
	m_pAdapter = DxAdapterSelector::Select(m_pFactory);

	DXGI_ADAPTER_DESC3 desc;
	m_pAdapter->GetDesc3(&desc);
	std::string gpuName = GetGpuNameStr(desc);
	u32 vramMb = static_cast<u32>(desc.DedicatedVideoMemory / 1024 / 1024);

	DXINFO("Selected Adapter --- {} --- VRAM {} MB", gpuName, vramMb);
}


void DxDeviceDebug::Enable(const ComPtr<ID3D12Device10>& pDevice)
{
	DXTRACE("Enabling");

	ComPtr<ID3D12InfoQueue> pInfoQueue;
	HRESULT hr = pDevice.As(&pInfoQueue);

	if (SUCCEEDED(hr))
	{
		pInfoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_CORRUPTION, TRUE);
		pInfoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_ERROR, TRUE);
		pInfoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_WARNING, TRUE);

		// Suppress whole categories of messages
		// D3D12_MESSAGE_CATEGORY Categories[] = {};

		// Suppress messages based on their severity level
		D3D12_MESSAGE_SEVERITY Severities[]{ D3D12_MESSAGE_SEVERITY_INFO };

		// Suppress individual messages by their ID
		D3D12_MESSAGE_ID DenyIds[] = {
			D3D12_MESSAGE_ID_CLEARRENDERTARGETVIEW_MISMATCHINGCLEARVALUE,   // I'm really not sure how to avoid this message.
			D3D12_MESSAGE_ID_MAP_INVALID_NULLRANGE,                         // This warning occurs when using capture frame while graphics debugging.
			D3D12_MESSAGE_ID_UNMAP_INVALID_NULLRANGE,                       // This warning occurs when using capture frame while graphics debugging.
		};

		D3D12_INFO_QUEUE_FILTER NewFilter = {};
		// NewFilter.DenyList.NumCategories = _countof(Categories);
		// NewFilter.DenyList.pCategoryList = Categories;
		NewFilter.DenyList.NumSeverities = _countof(Severities);
		NewFilter.DenyList.pSeverityList = Severities;
		NewFilter.DenyList.NumIDs = _countof(DenyIds);
		NewFilter.DenyList.pIDList = DenyIds;

		hr = pInfoQueue->PushStorageFilter(&NewFilter);
		DXASSERT(hr);
	}

	/*
	hr = pDevice->QueryInterface(IID_PPV_ARGS(m_Handle.ReleaseAndGetAddressOf()));
	DXASSERT(hr);
	*/
	DXTRACE("Enabled Device");
}


void DxDeviceDebug::Report()
{
	DXTRACE("Reporting");

	/*
	D3D12_RLDO_FLAGS flags =
		D3D12_RLDO_SUMMARY | D3D12_RLDO_DETAIL | D3D12_RLDO_IGNORE_INTERNAL;

	HRESULT hr = m_Handle->ReportLiveDeviceObjects(flags);
	DXASSERT(hr);
	*/
	DXDEBUG("Reported");
}


void DxDevice::Create(const ComPtr<IDXGIAdapter4>& pAdapter)
{
	DXTRACE("Creating");

	HRESULT hr = D3D12CreateDevice(pAdapter.Get(), L_D3D12_MIN_FEATURE_LEVEL, IID_PPV_ARGS(m_pHandle.ReleaseAndGetAddressOf()));
	DXASSERT(hr);

	m_pHandle->SetName(L"LumineEngineGraphicsBackendD3D12");

#if LUMINE_DEBUG
	m_DebugDevice.Enable(m_pHandle);
#endif

	DXDEBUG("Created");
}


void DxDevice::Destroy()
{
	DXTRACE("Destroying");

#if LUMINE_DEBUG
	m_DebugDevice.Report();
#endif

	DXDEBUG("Destroyed");
}

}
