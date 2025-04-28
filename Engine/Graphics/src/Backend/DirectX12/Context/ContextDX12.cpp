
module;

#include "Types.h"
#include "LoggerDX12.h"
#include <wrl/client.h>
#include <dxgi1_6.h>
#include <d3d12.h>
#include <vector>

module ContextDX12;

import FactoryDX12;
import DeviceDX12;


namespace lumine::graphics::dx12
{

void ContextDX12::Create()
{
	DXTRACE("Creating");

	m_Factory.Create();
	m_Device.Create(m_Factory.HandleAdapter());

	m_bCreated = true;
	DXDEBUG("Created");
}

void ContextDX12::Destroy()
{
	DXTRACE("Destroying");

	if (m_bCreated)
	{
		m_Device.Destroy();
		m_Factory.Destroy();
	}

	m_bCreated = false;
	DXDEBUG("Destroyed");
}

}
