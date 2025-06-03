
module;

#include "LoggerDX12.h"
#include <wrl/client.h>
#include <dxgi1_6.h>
#include <d3d12.h>
#include <directx/d3dx12.h>
#include <vector>

module SwapchainDX12;

using Microsoft::WRL::ComPtr;

import GraphicsSpecification;
import SpecificationDX12;


namespace lumine::graphics::dx12
{

void DxSwapchain::Create(const GraphicsSpecification& specs,
						 const ComPtr<IDXGIFactory7>& pFactory,
						 const ComPtr<ID3D12Device10>& pDevice,
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
		.SampleDesc = DXGI_SAMPLE_DESC{.Count = 1, .Quality = 0 },
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
	m_DxRtvHeap.Create(pDevice, D3D12_DESCRIPTOR_HEAP_TYPE_RTV, m_BackBufferCount);

	DXDEBUG("Created");
}


void DxSwapchain::UpdateRTVs(const ComPtr<ID3D12Device10>& pDevice)
{
	DXTRACE("Updating");

	m_rtvDescriptorSize = pDevice->GetDescriptorHandleIncrementSize(m_DxRtvHeap.Type());
	D3D12_CPU_DESCRIPTOR_HANDLE descHandle = m_DxRtvHeap.Handle()->GetCPUDescriptorHandleForHeapStart();
	CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(descHandle);

	for (UINT i = 0; i < m_BackBufferCount; ++i)
	{
		ComPtr<ID3D12Resource> pBackBuffer{ nullptr };

		HRESULT hr = m_pSwapchain->GetBuffer(i, IID_PPV_ARGS(&pBackBuffer));
		DXASSERT(hr);

		{
			std::wstring backBufferName{ L"SwapchainBuffer_" + std::to_wstring(i) };
			pBackBuffer->SetName(backBufferName.c_str());
		}

		pDevice->CreateRenderTargetView(pBackBuffer.Get(), nullptr, rtvHandle);

		m_BackBufferVector[i] = pBackBuffer;

		rtvHandle.Offset(m_rtvDescriptorSize);
	}

	DXDEBUG("Updated");
}


void DxSwapchain::Present() const
{
	const UINT syncInterval = 1;
	const UINT flags = 0;
	HRESULT hr = m_pSwapchain->Present(syncInterval, flags);
	DXASSERT(hr);
}


UINT DxSwapchain::GetCurrentFrameIndex() const
{
	return m_pSwapchain->GetCurrentBackBufferIndex();
}


bool DxSwapchain::IsTearingSupported(const ComPtr<IDXGIFactory7>& pFactory)
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
