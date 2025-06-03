
module;

#include "LoggerDX12.h"
#include <wrl/client.h>
#include <d3d12.h>
#include <directx/d3dx12.h>
#include <random> // TODO: Remove

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

	WaitForPreviousFrame();

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
	dxCmdQueue.Execute(ppCommandLists, m_DxFence);

	dxSwapchain.Present();

	WaitForPreviousFrame();
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
	const ComPtr<ID3D12GraphicsCommandList10>& pCommandList = m_DxCmdList.Handle();

	const DxSwapchain& dxSwapchain = m_Context.Swapchain();
	const std::vector<ComPtr<ID3D12Resource>>& backBuffers = dxSwapchain.GetBackBuffers();
	
	const UINT rtvDescriptorSize = dxSwapchain.GetRtvDescriptorSize();
	const DxDescriptorHeap& rtvHeap = dxSwapchain.GetRtvHeap();
	
	const UINT currentFrameIndex = dxSwapchain.GetCurrentFrameIndex();
	ID3D12Resource* pCurrentBackBuffer = backBuffers[currentFrameIndex].Get();

	// Impl
	HRESULT hr = dxCmdAllocator.Handle()->Reset();
	DXASSERT(hr);

	pCommandList->Reset(dxCmdAllocator.Handle().Get(), m_pipelineState.Get());

	// Record Commands

	{ // Indicate to use Back Buffer as Render Target
		constexpr int numBarriers{ 1 };
		CD3DX12_RESOURCE_BARRIER resourceBarrier = CD3DX12_RESOURCE_BARRIER::Transition(
			pCurrentBackBuffer, D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
		pCommandList->ResourceBarrier(numBarriers, &resourceBarrier);
	}

	{ // Clear screen
		CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(rtvHeap.Handle()->GetCPUDescriptorHandleForHeapStart(),
			currentFrameIndex, rtvDescriptorSize);
		const float clearColor[]{ GenerateRandomFloat(), 0.f, GenerateRandomFloat(), 1.0f};
		const UINT numRects = 0;
		pCommandList->ClearRenderTargetView(rtvHandle, clearColor, numRects, nullptr);
	}

	{ // Change Back Buffer state from Render Target to Window Present
		constexpr int numBarriers{ 1 };
		CD3DX12_RESOURCE_BARRIER resourceBarrier = CD3DX12_RESOURCE_BARRIER::Transition(
			pCurrentBackBuffer, D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
		pCommandList->ResourceBarrier(numBarriers, &resourceBarrier);
	}

	hr = pCommandList->Close();
	DXASSERT(hr);
}


void InterfaceDX12::WaitForPreviousFrame()
{
	const DxCommandQueue& dxCmdQueue = m_Context.CmdQueue();

	HRESULT hr = dxCmdQueue.Handle()->Signal(m_DxFence.Handle().Get(), m_DxFence.GetAvailableValue());
	DXASSERT(hr);

	m_DxFence.UpdateValue();

	if (not m_DxFence.IsSubmittedWorkCompleted())
	{
		m_DxFence.Wait();
	}

}

}
