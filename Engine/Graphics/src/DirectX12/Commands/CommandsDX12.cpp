
module;

#include "LoggerDX12.h"
#include <wrl/client.h>
#include <d3d12.h>
#include <directx/d3dx12.h>
#include <span>

module CommandsDX12;

import SynchronizationDX12;
import SwapchainDX12;

using Microsoft::WRL::ComPtr;


namespace lumine::graphics::dx12
{

void DxCommandAllocator::Create(const ComPtr<ID3D12Device10>& pDevice, D3D12_COMMAND_LIST_TYPE type)
{
	DXTRACE("Creating");

	m_Type = type;
	HRESULT hr = pDevice->CreateCommandAllocator(type, IID_PPV_ARGS(&m_pHandle));
	DXASSERT(hr);

	DXDEBUG("Created");
}


void DxCommandAllocator::Reset() const
{
	HRESULT hr = m_pHandle->Reset();
	DXASSERT(hr);
}


void DxCommandList::Create(const ComPtr<ID3D12Device10>& pDevice, const DxCommandAllocator& dxCommandAllocator)
{
	DXTRACE("Creating");

	UINT nodeMask = 0;
	ID3D12PipelineState* pPipelinInitialState{ nullptr };
	HRESULT hr = pDevice->CreateCommandList(nodeMask, dxCommandAllocator.Type(),
											dxCommandAllocator.Handle().Get(),
											pPipelinInitialState,
											IID_PPV_ARGS(&m_pHandle));
	DXASSERT(hr);

	hr = m_pHandle->Close();
	DXASSERT(hr);

	m_pDxCmdAllocator = &dxCommandAllocator;

	DXDEBUG("Created");
}


void DxCommandList::Reset(ID3D12PipelineState* pPipelineState) const
{
	HRESULT hr = m_pHandle->Reset(m_pDxCmdAllocator->Handle().Get(), pPipelineState);
	DXASSERT(hr);
}


void DxCommandList::EndRecording() const
{
	HRESULT hr = m_pHandle->Close();
	DXASSERT(hr);
}


void DxCommandList::ResourceBarrier(ID3D12Resource* pResource,
									D3D12_RESOURCE_STATES stateBefore, D3D12_RESOURCE_STATES stateAfter) const
{
	constexpr int numBarriers{ 1 };
	CD3DX12_RESOURCE_BARRIER resourceBarrier =
		CD3DX12_RESOURCE_BARRIER::Transition(pResource, stateBefore, stateAfter);
	m_pHandle->ResourceBarrier(numBarriers, &resourceBarrier);
}


void DxCommandList::ClearRenderTarget(const DxSwapchain& dxSwapchain, std::span<const float> clearColor)
{
	const UINT rtvDescriptorSize = dxSwapchain.GetRtvDescriptorSize();
	const DxDescriptorHeap& rtvHeap = dxSwapchain.GetRtvHeap();
	const UINT currentFrameIndex = dxSwapchain.GetCurrentFrameIndex();

	CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(rtvHeap.Handle()->GetCPUDescriptorHandleForHeapStart(),
											currentFrameIndex, rtvDescriptorSize);
	const UINT numRects{ 0 };
	const D3D12_RECT* pRects{ nullptr };

	m_pHandle->ClearRenderTargetView(rtvHandle, clearColor.data(), numRects, pRects);
}


void DxCommandQueue::Create(const ComPtr<ID3D12Device10>& pDevice)
{
	DXTRACE("Creating");

	D3D12_COMMAND_QUEUE_DESC queueDesc{
		.Type = D3D12_COMMAND_LIST_TYPE_DIRECT,
		.Priority = 0,
		.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE,
		.NodeMask = 0
	};
	HRESULT hr = pDevice->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(m_pHandle.ReleaseAndGetAddressOf()));
	DXASSERT(hr);

	DXDEBUG("Created");
}


void DxCommandQueue::Execute(std::span<ID3D12CommandList*> commandLists) const
{
	m_pHandle->ExecuteCommandLists(commandLists.size(), commandLists.data());
}


void DxCommandQueue::Signal(DxFence& dxFence) const
{
	HRESULT hr = m_pHandle->Signal(dxFence.Handle().Get(), dxFence.GetAvailableValue());
	DXASSERT(hr);

	dxFence.UpdateValue();
}

}
