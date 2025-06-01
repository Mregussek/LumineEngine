
module;

#include "Types.h"
#include "LoggerDX12.h"
#include <wrl/client.h>
#include <dxgi1_6.h>
#include <d3d12.h>
#include <directx/d3dx12.h>
#include <map>

module ContextDX12;

import GraphicsSpecification;
import SpecificationDX12;
import UtilitiesDX12;


namespace lumine::graphics::dx12
{

void ContextDX12::Create(const GraphicsSpecification& specs)
{
	DXTRACE("Creating");

	m_DxFactory.Create();
	m_DxDevice.Create(m_DxFactory.m_pAdapter);
	m_DxCommandInterface.Create(m_DxDevice.m_Device);

	m_DxSwapchain.Create(specs, m_DxFactory.m_pFactory, m_DxCommandInterface.m_pCommandQueue);
	m_DxSwapchainDescriptorHeap.Create(m_DxDevice.m_Device, D3D12_DESCRIPTOR_HEAP_TYPE_RTV, m_DxSwapchain.m_BackBufferCount);
	m_DxSwapchain.UpdateRTVs(m_DxDevice.m_Device, m_DxSwapchainDescriptorHeap);

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


void ContextDX12::DxFactoryDebug::Enable(UINT& dxgiFactoryFlags)
{
	DXTRACE("Enabling");

	ID3D12Debug6* pTmpDebug{ nullptr };

	HRESULT hr = D3D12GetDebugInterface(IID_PPV_ARGS(&pTmpDebug));
	DXASSERT(hr);

	hr = pTmpDebug->QueryInterface(IID_PPV_ARGS(&m_Handle));
	DXASSERT(hr);

	m_Handle->EnableDebugLayer();
	m_Handle->SetEnableGPUBasedValidation(true);

	dxgiFactoryFlags |= DXGI_CREATE_FACTORY_DEBUG;

	pTmpDebug->Release();

	DXTRACE("Enabled Factory");
}


u32 ContextDX12::DxAdapterSelector::GetScore(IDXGIAdapter4* pAdapter)
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


Microsoft::WRL::ComPtr<IDXGIAdapter4> ContextDX12::DxAdapterSelector::Select(const ComPtr<IDXGIFactory7>& pFactoryHandle)
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


void ContextDX12::DxFactory::Create()
{
	DXTRACE("Creating");

	CreateFactory();
	SelectAdapter();

	DXDEBUG("Created");
}


void ContextDX12::DxFactory::CreateFactory()
{
	UINT dxgiFactoryFlags{ 0 };

#if LUMINE_DEBUG
	m_DebugFactory.Enable(dxgiFactoryFlags);
#endif

	HRESULT hr = CreateDXGIFactory2(dxgiFactoryFlags, IID_PPV_ARGS(m_pFactory.ReleaseAndGetAddressOf()));
	DXASSERT(hr);
}


void ContextDX12::DxFactory::SelectAdapter()
{
	m_pAdapter = DxAdapterSelector::Select(m_pFactory);

	DXGI_ADAPTER_DESC3 desc;
	m_pAdapter->GetDesc3(&desc);
	std::string gpuName = GetGpuNameStr(desc);
	u32 vramMb = static_cast<u32>(desc.DedicatedVideoMemory / 1024 / 1024);

	DXINFO("Selected Adapter --- {} --- VRAM {} MB", gpuName, vramMb);
}


void ContextDX12::DxDeviceDebug::Enable(const ComPtr<ID3D12Device10>& pDevice)
{
	DXTRACE("Enabling");

	ComPtr<ID3D12InfoQueue> pInfoQueue;
	HRESULT hr = pDevice.As(&pInfoQueue);

	if (SUCCEEDED(hr))
	{
		pInfoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_CORRUPTION, TRUE);
		pInfoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_ERROR, TRUE);
		pInfoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_WARNING, TRUE);

		//Suppress whole categories of messages
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
		//NewFilter.DenyList.NumCategories = _countof(Categories);
		//NewFilter.DenyList.pCategoryList = Categories;
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


void ContextDX12::DxDeviceDebug::Report()
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


void ContextDX12::DxDevice::Create(const ComPtr<IDXGIAdapter4>& pAdapter)
{
	DXTRACE("Creating");

	HRESULT hr = D3D12CreateDevice(pAdapter.Get(), L_D3D12_MIN_FEATURE_LEVEL, IID_PPV_ARGS(m_Device.ReleaseAndGetAddressOf()));
	DXASSERT(hr);

	m_Device->SetName(L"LumineEngineGraphicsBackendD3D12");

#if LUMINE_DEBUG
	m_DebugDevice.Enable(m_Device);
#endif

	DXDEBUG("Created");
}


void ContextDX12::DxDevice::Destroy()
{
	DXTRACE("Destroying");

#if LUMINE_DEBUG
	m_DebugDevice.Report();
#endif

	DXDEBUG("Destroyed");
}


void ContextDX12::DxCommandInterface::Create(const ComPtr<ID3D12Device10>& pDevice)
{
	DXTRACE("Creating");

	CreateQueue(pDevice);

	DXDEBUG("Created");
}


void ContextDX12::DxCommandInterface::CreateQueue(const ComPtr<ID3D12Device10>& pDevice)
{
	D3D12_COMMAND_QUEUE_DESC queueDesc{
		.Type = D3D12_COMMAND_LIST_TYPE_DIRECT,
		.Priority = 0,
		.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE,
		.NodeMask = 0
	};
	HRESULT hr = pDevice->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(m_pCommandQueue.ReleaseAndGetAddressOf()));
	DXASSERT(hr);
}


void ContextDX12::DxDescriptorHeap::Create(const ComPtr<ID3D12Device10>& pDevice, D3D12_DESCRIPTOR_HEAP_TYPE type,
	UINT numDescriptors)
{
	DXTRACE("Creating");

	m_Type = type;
	m_NumDescriptors = numDescriptors;

	D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc{
		.Type = m_Type,
		.NumDescriptors = m_NumDescriptors,
		.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE,
		.NodeMask = 0
	};

	HRESULT hr = pDevice->CreateDescriptorHeap(&descHeapDesc, IID_PPV_ARGS(m_pDescriptorHeap.ReleaseAndGetAddressOf()));
	DXASSERT(hr);

	DXDEBUG("Created");
}


void ContextDX12::DxSwapchain::Create(const GraphicsSpecification& specs,
									  const ComPtr<IDXGIFactory7>& pFactory,
									  const ComPtr<ID3D12CommandQueue>& pCommandQueue)
{
	DXTRACE("Creating");

	m_BackBufferCount = specs.swapchainBackBufferCount;

	UINT flags{ 0 };
	if (IsTearingSupported(pFactory))
	{
		flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING;
	}

	DXGI_FORMAT format = SpecificationAdapterDX12::Format(specs.swapchainFormat);

	DXGI_SWAP_CHAIN_DESC1 swapchainDesc{
		.Width = specs.windowWidth,
		.Height = specs.windowHeight,
		.Format = format,
		.Stereo = FALSE,
		.SampleDesc = { 1, 0 },
		.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT,
		.BufferCount = m_BackBufferCount,
		.Scaling = DXGI_SCALING_STRETCH,
		.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD,
		.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED,
		.Flags = flags
	};
	
	ComPtr<IDXGISwapChain1> pSwapchain1{ nullptr };
	HRESULT hr = pFactory->CreateSwapChainForHwnd(pCommandQueue.Get(), specs.windowRawHandle.hwnd, &swapchainDesc,
												  nullptr, nullptr, pSwapchain1.ReleaseAndGetAddressOf());
	DXASSERT(hr);

	// Disable the Alt+Enter full-screen toggle feature. Switching to full-screen will be handled manually.
	hr = pFactory->MakeWindowAssociation(specs.windowRawHandle.hwnd, DXGI_MWA_NO_ALT_ENTER);
	DXASSERT(hr);

	hr = pSwapchain1.As(&m_pSwapchain);
	DXASSERT(hr);

	m_BackBufferVector.resize(m_BackBufferCount);

	DXDEBUG("Created");
}


void ContextDX12::DxSwapchain::UpdateRTVs(const ComPtr<ID3D12Device10>& pDevice, const DxDescriptorHeap& dxDescriptorHeap)
{
	DXTRACE("Updating");

	UINT rtvDescriptorSize = pDevice->GetDescriptorHandleIncrementSize(dxDescriptorHeap.m_Type);
	D3D12_CPU_DESCRIPTOR_HANDLE descHandle = dxDescriptorHeap.m_pDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
	CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(descHandle);

	for (UINT i = 0; i < m_BackBufferCount; ++i)
	{
		ComPtr<ID3D12Resource> pBackBuffer{ nullptr };

		HRESULT hr = m_pSwapchain->GetBuffer(i, IID_PPV_ARGS(&pBackBuffer));
		DXASSERT(hr);

		pDevice->CreateRenderTargetView(pBackBuffer.Get(), nullptr, rtvHandle);

		m_BackBufferVector[i] = pBackBuffer;

		rtvHandle.Offset(rtvDescriptorSize);
	}

	DXDEBUG("Updated");
}


bool ContextDX12::DxSwapchain::IsTearingSupported(const ComPtr<IDXGIFactory7>& pFactory)
{
	BOOL bTearingSupported = false;
	HRESULT hr = pFactory->CheckFeatureSupport(DXGI_FEATURE_PRESENT_ALLOW_TEARING,
											   &bTearingSupported, sizeof(bTearingSupported));
	if (SUCCEEDED(hr) && bTearingSupported == TRUE)
	{
		DXDEBUG("Tearing is supported");
		return true;
	}

	DXWARN("Tearing is not supported");
	return false;
}


}
