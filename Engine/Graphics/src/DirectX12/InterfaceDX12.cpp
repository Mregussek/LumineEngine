
module;

#include "LoggerDX12.h"

module InterfaceDX12;

import SpecificationDX12;


namespace lumine::graphics::dx12
{

void InterfaceDX12::Initialize(const GraphicsSpecification& specs)
{
	DXCREATE_LOGGER();
	DXTRACE("Initializing");

	SpecificationDX12 specsDX12{};

	m_Context.Create(specsDX12);

	m_bInitialized = true;
	DXDEBUG("Initialized");
}

void InterfaceDX12::Close()
{
	DXTRACE("Closing");

	if (m_bInitialized)
	{
		m_Context.Destroy();
	}

	m_bInitialized = false;
	DXDEBUG("Closed");
}

}
