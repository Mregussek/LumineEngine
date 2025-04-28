
module;

#include "LoggerDX12.h"
#include <wrl/client.h>
#include <dxgi1_6.h>
#include <d3d12.h>

module DeviceDX12;

import UtilitiesDX12;


namespace lumine::graphics::dx12
{

void DeviceDX12::Create(const ComPtr<IDXGIAdapter4>& pAdapter)
{
	DXTRACE("Creating");
	
	HRESULT hr = D3D12CreateDevice(pAdapter.Get(), L_D3D12_MIN_FEATURE_LEVEL, IID_PPV_ARGS(m_Device.ReleaseAndGetAddressOf()));
	DXASSERT(hr);
	
	m_Device->SetName(L"LumineEngineGraphicsBackendD3D12");

	if constexpr (LUMINE_DEBUG)
	{
		m_DebugDevice.Enable(m_Device);
	}

	m_bCreated = true;
	DXDEBUG("Created");
}


void DeviceDX12::Destroy()
{
	DXTRACE("Destroying");

	if (m_bCreated)
	{
		if constexpr (LUMINE_DEBUG)
		{
			m_DebugDevice.Destroy();
		}

		m_Device->Release();
	}

	m_bCreated = false;
	DXDEBUG("Destroyed");
}

}
