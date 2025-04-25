
module;

#include "Types.h"
#include "LoggerDX12.h"
#include <dxgi1_6.h>

module ContextDX12;

import AssertsDX12;


namespace lumine::graphics::dx12
{

ErrorStatus ContextDX12::Create()
{
	DXTRACE("Creating");

	HRESULT hr = CreateDXGIFactory2(0, IID_PPV_ARGS(m_DxFactory.ReleaseAndGetAddressOf()));
	AssertDX12(hr);

	DXDEBUG("Created");
	return ErrorStatus::OK;
}

void ContextDX12::Destroy()
{
	DXDEBUG("Destroyed");
}

}
