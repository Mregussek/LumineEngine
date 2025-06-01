
module;

#include "Types.h"
#include <wrl/client.h>
using namespace Microsoft::WRL;
#include <dxgi1_6.h>
#include <d3d12.h>
#include <vector>

export module ContextDX12;

import GraphicsSpecification;


export namespace lumine::graphics::dx12
{

class ContextDX12
{
public:

	void Create(const GraphicsSpecification& specs);
	void Destroy();

private:

	struct DxFactoryDebug
	{
		void Enable(UINT& dxgiFactoryFlags);

		ComPtr<ID3D12Debug6> m_Handle{ nullptr };
	};

	struct DxAdapterSelector
	{
		static ComPtr<IDXGIAdapter4> Select(const ComPtr<IDXGIFactory7>& pFactoryHandle);

	private:

		static u32 GetScore(IDXGIAdapter4* pAdapter);

	};

	struct DxFactory
	{
		void Create();

		ComPtr<IDXGIFactory7> m_pFactory{ nullptr };
		ComPtr<IDXGIAdapter4> m_pAdapter{ nullptr };
#if LUMINE_DEBUG
		DxFactoryDebug m_DebugFactory{};
#endif

	private:

		void CreateFactory();
		void SelectAdapter();

	};

	struct DxDeviceDebug
	{
		void Enable(const ComPtr<ID3D12Device10>& pDevice);
		void Report();

		ComPtr<ID3D12DebugDevice2> m_Handle{ nullptr };
	};

	struct DxDevice
	{
		void Create(const ComPtr<IDXGIAdapter4>& pAdapter);
		void Destroy();

		ComPtr<ID3D12Device10> m_Device{ nullptr };

#if LUMINE_DEBUG
		DxDeviceDebug m_DebugDevice{};
#endif
	};

	struct DxCommandAllocator
	{
		ComPtr<ID3D12CommandAllocator> m_pCommandAllocator{ nullptr };
		D3D12_COMMAND_LIST_TYPE m_Type{ D3D12_COMMAND_LIST_TYPE_NONE };
	};

	struct DxCommandInterface
	{
		[[nodiscard]] static ComPtr<ID3D12CommandQueue> CreateQueue(const ComPtr<ID3D12Device10>& pDevice);

		[[nodiscard]] static DxCommandAllocator CreateAllocator(
			const ComPtr<ID3D12Device10>& pDevice, D3D12_COMMAND_LIST_TYPE type);

		[[nodiscard]] static ComPtr<ID3D12GraphicsCommandList> CreateGraphicsList(
			const ComPtr<ID3D12Device10>& pDevice, const DxCommandAllocator& dxCommandAllocator);
	};

	struct DxDescriptorHeap
	{
		[[nodiscard]] static ComPtr<ID3D12DescriptorHeap> Create(
			const ComPtr<ID3D12Device10>& pDevice, D3D12_DESCRIPTOR_HEAP_TYPE type, UINT numDescriptors);
	};

	struct DxSwapchain
	{
		void Create(const GraphicsSpecification& specs,
					const ComPtr<IDXGIFactory7>& pFactory,
					const ComPtr<ID3D12Device10>& pDevice,
					const ComPtr<ID3D12CommandQueue>& pCommandQueue);

		void UpdateRTVs(const ComPtr<ID3D12Device10>& pDevice);


		ComPtr<IDXGISwapChain4> m_pSwapchain{ nullptr };
		ComPtr<ID3D12DescriptorHeap> m_pDescriptorHeap{ nullptr };
		const D3D12_DESCRIPTOR_HEAP_TYPE m_DescriptorHeapType{ D3D12_DESCRIPTOR_HEAP_TYPE_RTV };
		UINT m_BackBufferCount{ 0 };

		std::vector<ComPtr<ID3D12Resource>> m_BackBufferVector{};

	private:

		[[nodiscard]] static bool IsTearingSupported(const ComPtr<IDXGIFactory7>& pFactory);

	};

private:

	DxFactory m_DxFactory{};
	DxDevice m_DxDevice{};
	ComPtr<ID3D12CommandQueue> m_pCommandQueue{ nullptr };
	DxSwapchain m_DxSwapchain{};

	std::vector<DxCommandAllocator> m_pCommandAllocators{};
	ComPtr<ID3D12GraphicsCommandList> m_CommandListGraphics{};
	
	bool m_bCreated{ false };

}; // ContextDX12

}
