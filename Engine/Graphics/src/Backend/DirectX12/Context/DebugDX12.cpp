
module;

#include "LoggerDX12.h"
#include <wrl/client.h>
#include <dxgi1_6.h>
#include <d3d12.h>

module DebugDX12;


namespace lumine::graphics::dx12
{

void DebugDX12::Enable(UINT& dxgiFactoryFlags)
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

	DXTRACE("Enabled");
}

}
