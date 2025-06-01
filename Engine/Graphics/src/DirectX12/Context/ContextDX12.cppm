
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


	class DxFactoryDebug
	{
	public:

		void Enable(UINT& dxgiFactoryFlags);

		[[nodiscard]] const ComPtr<ID3D12Debug6>& Handle() const { return m_pHandle; }

	private:

		ComPtr<ID3D12Debug6> m_pHandle{ nullptr };

	};


	class DxAdapterSelector
	{
	public:

		static ComPtr<IDXGIAdapter4> Select(const ComPtr<IDXGIFactory7>& pFactoryHandle);

	private:

		static u32 GetScore(IDXGIAdapter4* pAdapter);

	};


	class DxFactory
	{
	public:

		void Create();

		[[nodiscard]] const ComPtr<IDXGIFactory7> Handle() const { return m_pFactory; }
		[[nodiscard]] const ComPtr<IDXGIAdapter4> Adapter() const { return m_pAdapter; }

	private:

		void CreateFactory();
		void SelectAdapter();

	private:

		ComPtr<IDXGIFactory7> m_pFactory{ nullptr };
		ComPtr<IDXGIAdapter4> m_pAdapter{ nullptr };
#if LUMINE_DEBUG
		DxFactoryDebug m_DebugFactory{};
#endif
	};


	class DxDeviceDebug
	{
	public:

		void Enable(const ComPtr<ID3D12Device10>& pDevice);
		void Report();

	private:

		ComPtr<ID3D12DebugDevice2> m_pHandle{ nullptr };

	};


	class DxDevice
	{
	public:

		void Create(const ComPtr<IDXGIAdapter4>& pAdapter);
		void Destroy();

		[[nodiscard]] const ComPtr<ID3D12Device10>& Handle() const { return m_pHandle; }

	private:

		ComPtr<ID3D12Device10> m_pHandle{ nullptr };

#if LUMINE_DEBUG
		DxDeviceDebug m_DebugDevice{};
#endif
	};


	class DxCommandQueue
	{
	public:

		void Create(const ComPtr<ID3D12Device10>& pDevice);

		[[nodiscard]] const ComPtr<ID3D12CommandQueue>& Handle() const { return m_pHandle; }

	private:

		ComPtr<ID3D12CommandQueue> m_pHandle{ nullptr };

	};


	class DxCommandAllocator
	{
	public:

		void Create(const ComPtr<ID3D12Device10>& pDevice, D3D12_COMMAND_LIST_TYPE type);

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

		[[nodiscard]] const ComPtr<ID3D12GraphicsCommandList>& Handle() const { return m_pHandle; }

	private:

		ComPtr<ID3D12GraphicsCommandList> m_pHandle{ nullptr };

	};


	class DxDescriptorHeap
	{
	public:

		void Create(const ComPtr<ID3D12Device10>& pDevice, D3D12_DESCRIPTOR_HEAP_TYPE type,
					UINT numDescriptors);

		[[nodiscard]] const ComPtr<ID3D12DescriptorHeap>& Handle() const { return m_pHandle; }
		[[nodiscard]] D3D12_DESCRIPTOR_HEAP_TYPE Type() const { return m_Type; }
		[[nodiscard]] UINT Num() const { return m_NumDescriptors; }
	
	private:

		ComPtr<ID3D12DescriptorHeap> m_pHandle{ nullptr };
		D3D12_DESCRIPTOR_HEAP_TYPE m_Type{ D3D12_DESCRIPTOR_HEAP_TYPE_RTV };
		UINT m_NumDescriptors{ 0 };

	};


	struct DxSwapchain
	{
		void Create(const GraphicsSpecification& specs,
			const ComPtr<IDXGIFactory7>& pFactory,
			const ComPtr<ID3D12Device10>& pDevice,
			const ComPtr<ID3D12CommandQueue>& pCommandQueue);

		void UpdateRTVs(const ComPtr<ID3D12Device10>& pDevice);

		[[nodiscard]] UINT GetCurrentFrameIndex() const;


		ComPtr<IDXGISwapChain4> m_pSwapchain{ nullptr };
		DxDescriptorHeap m_DxRtvHeap{};

		std::vector<ComPtr<ID3D12Resource>> m_BackBufferVector{};
		UINT m_BackBufferCount{ 0 };

	private:

		[[nodiscard]] static bool IsTearingSupported(const ComPtr<IDXGIFactory7>& pFactory);

	};


	class DxFence
	{
	public:

		void Create(const ComPtr<ID3D12Device10>& pDevice);

		[[nodiscard]] const ComPtr<ID3D12Fence1>& Handle() const { return m_pHandle; }

	private:

		ComPtr<ID3D12Fence1> m_pHandle{ nullptr };

	};


	struct DxFenceEvent
	{
		void Create();

		HANDLE m_FenceEvent{ nullptr };
	};


private:

	// Rendering Pipeline Dependencies
	DxFactory m_DxFactory{};
	DxDevice m_DxDevice{};
	DxCommandQueue m_DxCmdQueue{};
	DxSwapchain m_DxSwapchain{};
	std::vector<DxCommandAllocator> m_pDxCmdAllocators{};

	// Sample Assets
	DxCommandList m_DxCmdList{};
	DxFence m_DxFence{};
	DxFenceEvent m_DxFenceEvent{};

	bool m_bCreated{ false };

}; // ContextDX12

}
