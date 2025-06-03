
module;

#include <wrl/client.h>
#include <d3d12.h>
#include <span>

export module CommandsDX12;

import SynchronizationDX12;
import SwapchainDX12;

using Microsoft::WRL::ComPtr;


export namespace lumine::graphics::dx12
{

class DxCommandAllocator
{
public:

	void Create(const ComPtr<ID3D12Device10>& pDevice, D3D12_COMMAND_LIST_TYPE type);

	void Reset() const;

	[[nodiscard]] const ComPtr<ID3D12CommandAllocator>& Handle() const { return m_pHandle; }
	[[nodiscard]] D3D12_COMMAND_LIST_TYPE Type() const { return m_Type; }

private:

	ComPtr<ID3D12CommandAllocator> m_pHandle{ nullptr };
	D3D12_COMMAND_LIST_TYPE m_Type{ D3D12_COMMAND_LIST_TYPE_NONE };
};


class DxCommandList
{
public:

	void Create(const ComPtr<ID3D12Device10>& pDevice, const DxCommandAllocator& dxCommandAllocator);

	void Reset(ID3D12PipelineState* pPipelineState) const;

	[[nodiscard]] const ComPtr<ID3D12GraphicsCommandList10>& Handle() const { return m_pHandle; }

public:

	void EndRecording() const;

	void ResourceBarrier(ID3D12Resource* pResource, D3D12_RESOURCE_STATES stateBefore, D3D12_RESOURCE_STATES stateAfter) const;

	void ClearRenderTarget(const DxSwapchain& dxSwapchain, std::span<const float> clearColor);

private:

	ComPtr<ID3D12GraphicsCommandList10> m_pHandle{ nullptr };
	const DxCommandAllocator* m_pDxCmdAllocator{ nullptr };

};


class DxCommandQueue
{
public:

	void Create(const ComPtr<ID3D12Device10>& pDevice);

	void Execute(std::span<ID3D12CommandList*> commandLists) const;
	void Signal(DxFence& dxFence) const;

	[[nodiscard]] const ComPtr<ID3D12CommandQueue>& Handle() const { return m_pHandle; }

private:

	ComPtr<ID3D12CommandQueue> m_pHandle{ nullptr };

};

}
