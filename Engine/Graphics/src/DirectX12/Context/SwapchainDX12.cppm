
module;

#include <wrl/client.h>
#include <dxgi1_6.h>
#include <d3d12.h>
#include <vector>

export module SwapchainDX12;

using Microsoft::WRL::ComPtr;

import GraphicsSpecification;
import DescriptorHeapDX12;


export namespace lumine::graphics::dx12
{

class DxSwapchain
{
public:

	void Create(const GraphicsSpecification& specs,
				const ComPtr<IDXGIFactory7>& pFactory,
				const ComPtr<ID3D12Device10>& pDevice,
				const ComPtr<ID3D12CommandQueue>& pCommandQueue);

	void UpdateRTVs(const ComPtr<ID3D12Device10>& pDevice);


	[[nodiscard]] const ComPtr<IDXGISwapChain4>& Handle() const { return m_pSwapchain; }
	[[nodiscard]] UINT GetCurrentFrameIndex() const;
	[[nodiscard]] const std::vector<ComPtr<ID3D12Resource>>& GetBackBuffers() const { return m_BackBufferVector; }
	[[nodiscard]] UINT GetRtvDescriptorSize() const { return m_rtvDescriptorSize; }
	[[nodiscard]] const DxDescriptorHeap& GetRtvHeap() const { return m_DxRtvHeap; }

private:

	ComPtr<IDXGISwapChain4> m_pSwapchain{ nullptr };
	DxDescriptorHeap m_DxRtvHeap{};
	UINT m_rtvDescriptorSize{ 0 };

	std::vector<ComPtr<ID3D12Resource>> m_BackBufferVector{};
	UINT m_BackBufferCount{ 0 };

private:

	[[nodiscard]] static bool IsTearingSupported(const ComPtr<IDXGIFactory7>& pFactory);

};

}
