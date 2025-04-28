
module;

#include "Types.h"
#include "LoggerDX12.h"
#include <wrl/client.h>
#include <dxgi1_6.h>
#include <d3d12.h>
#include <vector>

module ContextDX12;

import DebugDX12;


namespace lumine::graphics::dx12
{

ErrorStatus ContextDX12::Create()
{
	DXTRACE("Creating");

	m_Factory.Create();

	DXDEBUG("Created");
	return ErrorStatus::OK;
}

void ContextDX12::Destroy()
{
	DXDEBUG("Destroyed");
}

}
