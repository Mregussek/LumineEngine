
module;

#include "Types.h"
#include "LoggerDX12.h"
#include <wrl/client.h>
#include <dxgi1_6.h>
#include <d3d12.h>

module ContextDX12;

import UtilitiesDX12;
import AdapterSelectorDX12;


namespace lumine::graphics::dx12
{

void ContextDX12::Create()
{
	DXTRACE("Creating");

	m_DxFactory.Create();
	m_DxDevice.Create(m_DxFactory.m_pAdapter);
	m_DxCommandInterface.Create(m_DxDevice.m_Device);

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
	m_pAdapter = AdapterSelectorDX12::Select(m_pFactory);

	DXGI_ADAPTER_DESC3 desc;
	m_pAdapter->GetDesc3(&desc);
	std::string gpuName = GetGpuNameStr(desc);
	u32 vramMb = static_cast<u32>(desc.DedicatedVideoMemory / 1024 / 1024);

	DXINFO("Selected Adapter --- {} --- VRAM {} MB", gpuName, vramMb);
}


void ContextDX12::DxDeviceDebug::Enable(const ComPtr<ID3D12Device>& pDevice)
{
	DXTRACE("Enabling");

	HRESULT hr = pDevice->QueryInterface(IID_PPV_ARGS(m_Handle.ReleaseAndGetAddressOf()));
	DXASSERT(hr);

	DXTRACE("Enabled Device");
}


void ContextDX12::DxDeviceDebug::Report()
{
	DXTRACE("Reporting");

	D3D12_RLDO_FLAGS flags =
		D3D12_RLDO_SUMMARY | D3D12_RLDO_DETAIL | D3D12_RLDO_IGNORE_INTERNAL;

	m_Handle->ReportLiveDeviceObjects(flags);

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


void ContextDX12::DxSwapchain::Create()
{
	DXTRACE("Creating");

	/*
	UINT Width;
	UINT Height;
	DXGI_FORMAT Format;
	BOOL Stereo;
	DXGI_SAMPLE_DESC SampleDesc;
	DXGI_USAGE BufferUsage;
	UINT BufferCount;
	DXGI_SCALING Scaling;
	DXGI_SWAP_EFFECT SwapEffect;
	DXGI_ALPHA_MODE AlphaMode;
	UINT Flags;
	*/

	DXGI_SWAP_CHAIN_DESC1 swapchainDesc{

	};

	DXDEBUG("Created");
}


}
