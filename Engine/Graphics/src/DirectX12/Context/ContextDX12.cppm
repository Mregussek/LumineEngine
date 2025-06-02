
module;

#include "Types.h"
#include <wrl/client.h>
#include <dxgi1_6.h>
#include <d3d12.h>

export module ContextDX12;

using Microsoft::WRL::ComPtr;

import GraphicsSpecification;
import CommandsDX12;
import SwapchainDX12;


namespace lumine::graphics::dx12
{

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


export class DxDevice
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


export class ContextDX12
{
public:

	void Create(const GraphicsSpecification& specs);
	void Destroy();

	[[nodiscard]] const DxDevice& Device() const { return m_DxDevice; }
	[[nodiscard]] const DxCommandAllocator& CmdAllocator() const { return m_pDxCmdAllocator; }
	[[nodiscard]] const DxCommandQueue& CmdQueue() const { return m_DxCmdQueue; }
	[[nodiscard]] const DxSwapchain& Swapchain() const { return m_DxSwapchain; }

private:

	DxFactory m_DxFactory{};
	DxDevice m_DxDevice{};
	DxCommandQueue m_DxCmdQueue{};
	DxSwapchain m_DxSwapchain{};
	DxCommandAllocator m_pDxCmdAllocator{};

	bool m_bCreated{ false };

}; // ContextDX12

}
