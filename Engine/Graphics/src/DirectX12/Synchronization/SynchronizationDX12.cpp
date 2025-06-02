
module;

#include "LoggerDX12.h"
#include <wrl/client.h>
#include <d3d12.h>

module SynchronizationDX12;

using Microsoft::WRL::ComPtr;


namespace lumine::graphics::dx12
{

void DxFence::Create(const ComPtr<ID3D12Device10>& pDevice)
{
	DXTRACE("Creating");

	HRESULT hr = pDevice->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_pHandle));
	DXASSERT(hr);

	m_Value = 1;

	DXDEBUG("Created");
}


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


void DxFenceEvent::Wait()
{
	WaitForSingleObject(m_Handle, INFINITE);
}

}
