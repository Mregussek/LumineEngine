
module;

#include "LoggerDX12.h"
#include <wrl/client.h>
#include <d3d12.h>
#include <directx/d3dx12.h>
#include <random> // TODO: Remove
#include <span>

module InterfaceDX12;

using Microsoft::WRL::ComPtr;

import SpecificationDX12;
import ContextDX12;
import CommandsDX12;
import SynchronizationDX12;
import SwapchainDX12;


namespace lumine::graphics::dx12
{

void InterfaceDX12::Initialize(const GraphicsSpecification& specs)
{
	DXCREATE_LOGGER();
	DXTRACE("Initializing");

	m_Context.Create(specs);

	const DxDevice& dxDevice = m_Context.Device();
	const DxCommandAllocator& dxCmdAllocator = m_Context.CmdAllocator();

	m_DxCmdList.Create(dxDevice.Handle(), dxCmdAllocator);
	m_DxFence.Create(dxDevice.Handle());

	m_bInitialized = true;
	DXINFO("Initialized");
}


void InterfaceDX12::Close()
{
	DXTRACE("Closing");

	if (not m_DxFence.IsSubmittedWorkCompleted())
	{
		m_DxFence.Wait();
	}

	if (m_bInitialized)
	{
		m_DxFence.Close();
		m_Context.Destroy();
	}

	m_bInitialized = false;
	DXINFO("Closed");
}


void InterfaceDX12::Present()
{
	PrepareCommands();

	const DxCommandQueue& dxCmdQueue = m_Context.CmdQueue();
	const DxSwapchain& dxSwapchain = m_Context.Swapchain();

	ID3D12CommandList* ppCommandLists[] = { m_DxCmdList.Handle().Get() };
	dxCmdQueue.Execute(ppCommandLists);

	dxSwapchain.Present();

	dxCmdQueue.Signal(m_DxFence);

	if (not m_DxFence.IsSubmittedWorkCompleted())
	{
		m_DxFence.Wait();
	}
}


// TODO: Remove
static float GenerateRandomFloat(float min = 0.0f, float max = 1.0f) {
	static thread_local std::mt19937 generator{ std::random_device{}() };
	std::uniform_real_distribution<float> distribution(min, max);
	return distribution(generator);
}


void InterfaceDX12::PrepareCommands()
{
	// Getters
	const DxCommandAllocator& dxCmdAllocator = m_Context.CmdAllocator();
	const DxSwapchain& dxSwapchain = m_Context.Swapchain();
	const ComPtr<ID3D12Resource> pCurrentBackBuffer = dxSwapchain.GetCurrentBackBuffer();

	dxCmdAllocator.Reset();
	m_DxCmdList.Reset(m_pipelineState.Get());

	// Record Commands

	m_DxCmdList.ResourceBarrier(pCurrentBackBuffer.Get(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);

	const float clearColor[]{ GenerateRandomFloat(), 0.f, GenerateRandomFloat(), 1.0f };
	m_DxCmdList.ClearRenderTarget(dxSwapchain, clearColor);

	m_DxCmdList.ResourceBarrier(pCurrentBackBuffer.Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);

	m_DxCmdList.EndRecording();
}

}
