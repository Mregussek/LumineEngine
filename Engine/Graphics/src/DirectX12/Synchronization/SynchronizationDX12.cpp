
module;

#include "LoggerDX12.h"
#include <wrl/client.h>
#include <d3d12.h>

module SynchronizationDX12;

using Microsoft::WRL::ComPtr;


namespace lumine::graphics::dx12
{


void DxFenceEvent::Create()
{
	DXTRACE("Creating");

	m_Handle = ::CreateEvent(NULL, FALSE, FALSE, NULL);
	if (not m_Handle)
	{
		DXASSERT(HRESULT_FROM_WIN32(GetLastError()));
	}

	m_bCreated = true;
	DXDEBUG("Created");
}


void DxFenceEvent::Close()
{
	DXTRACE("Closing");

	if (m_bCreated)
	{
		CloseHandle(m_Handle);
	}

	m_bCreated = false;
	DXDEBUG("Closed");
}


void DxFenceEvent::Wait() const
{
	WaitForSingleObject(m_Handle, INFINITE);
}


void DxFence::Create(const ComPtr<ID3D12Device10>& pDevice)
{
	DXTRACE("Creating");

	HRESULT hr = pDevice->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_pHandle));
	DXASSERT(hr);

	m_ValueSubmitted = 0;
	m_ValueAvailable = 1;

	m_DxEvent.Create();

	DXDEBUG("Created");
}


void DxFence::Close()
{
	DXTRACE("Closing");

	m_DxEvent.Close();

	DXDEBUG("Closed");
}


void DxFence::UpdateValue()
{
	m_ValueSubmitted = m_ValueAvailable;
	m_ValueAvailable++;
}


bool DxFence::IsSubmittedWorkCompleted() const
{
	return m_pHandle->GetCompletedValue() >= m_ValueSubmitted;
}


void DxFence::Wait() const
{
	HRESULT hr = m_pHandle->SetEventOnCompletion(m_ValueSubmitted, m_DxEvent.Handle());
	DXASSERT(hr);
	m_DxEvent.Wait();
}

}
