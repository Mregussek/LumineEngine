
module;

#include "LoggerDX12.h"
#include <wrl/client.h>
#include <d3d12.h>
#include <span>

module CommandsDX12;

import SynchronizationDX12;

using Microsoft::WRL::ComPtr;


namespace lumine::graphics::dx12
{

void DxCommandAllocator::Create(const ComPtr<ID3D12Device10>& pDevice,
	D3D12_COMMAND_LIST_TYPE type)
{
	DXTRACE("Creating");

	m_Type = type;
	HRESULT hr = pDevice->CreateCommandAllocator(type, IID_PPV_ARGS(&m_pHandle));
	DXASSERT(hr);

	DXDEBUG("Created");
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

	DXDEBUG("Created");
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


void DxCommandQueue::Execute(std::span<ID3D12CommandList*> commandLists, DxFence& dxFence) const
{
	m_pHandle->ExecuteCommandLists(commandLists.size(), commandLists.data());
}

}
