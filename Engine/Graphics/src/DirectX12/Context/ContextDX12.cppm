
module;

#include "Types.h"
#include <wrl/client.h>
#include <dxgi1_6.h>
#include <d3d12.h>

export module ContextDX12;

import SpecificationDX12;


export namespace lumine::graphics::dx12
{

class ContextDX12
{
	template<typename T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public:

	void Create(const SpecificationDX12& specs);
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
		void Enable(const ComPtr<ID3D12Device>& pDevice);
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

	struct DxCommandInterface
	{
		void Create(const ComPtr<ID3D12Device10>& pDevice);

		ComPtr<ID3D12CommandQueue> m_pCommandQueue{ nullptr };
		ComPtr<ID3D12CommandAllocator> m_pCommandAllocator{ nullptr };
		ComPtr<ID3D12GraphicsCommandList> m_pCommandList{ nullptr };

	private:

		void CreateQueue(const ComPtr<ID3D12Device10>& pDevice);

	};

	struct DxSwapchain
	{
		void Create();

	};

private:

	DxFactory m_DxFactory{};
	DxDevice m_DxDevice{};
	DxCommandInterface m_DxCommandInterface{};
	bool m_bCreated{ false };

}; // ContextDX12

}
