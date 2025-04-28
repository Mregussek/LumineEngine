
module;

#include "LoggerDX12.h"
#include <wrl/client.h>
#include <dxgi1_6.h>
#include <d3d12.h>

module DebugDX12;


namespace lumine::graphics::dx12
{

void DebugFactoryDX12::Enable(UINT& dxgiFactoryFlags)
{
	DXTRACE("Enabling");

	ID3D12Debug6* pTmpDebug{ nullptr };

	HRESULT hr = D3D12GetDebugInterface(IID_PPV_ARGS(&pTmpDebug));
	DXASSERT(hr);

	hr = pTmpDebug->QueryInterface(IID_PPV_ARGS(&m_DebugController));
	DXASSERT(hr);

	m_DebugController->EnableDebugLayer();
	m_DebugController->SetEnableGPUBasedValidation(true);

	dxgiFactoryFlags |= DXGI_CREATE_FACTORY_DEBUG;

	pTmpDebug->Release();

	m_bEnabled = true;
	DXTRACE("Enabled Factory");
}


void DebugFactoryDX12::Destroy()
{
	DXTRACE("Destroying");

	if (m_bEnabled)
	{
		m_DebugController->Release();
		m_DebugController.Reset();
	}

	m_bEnabled = false;
	DXDEBUG("Destroyed Factory");
}



void DebugDeviceDX12::Enable(const ComPtr<ID3D12Device>& pDevice)
{
	DXTRACE("Enabling");
	HRESULT hr = pDevice->QueryInterface(IID_PPV_ARGS(m_DebugDevice.ReleaseAndGetAddressOf()));
	DXASSERT(hr);

	m_bEnabled = true;
	DXTRACE("Enabled Device");
}


void DebugDeviceDX12::Destroy()
{
	DXTRACE("Destroying");

	if (m_bEnabled)
	{
		D3D12_RLDO_FLAGS flags =
			D3D12_RLDO_SUMMARY | D3D12_RLDO_DETAIL | D3D12_RLDO_IGNORE_INTERNAL;

		m_DebugDevice->ReportLiveDeviceObjects(flags);

		m_DebugDevice->Release();
		m_DebugDevice.Reset();
	}

	m_bEnabled = false;
	DXDEBUG("Destroyed Device");
}

}
