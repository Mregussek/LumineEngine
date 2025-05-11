
module;

#include "LoggerDX12.h"

module InterfaceDX12;


namespace lumine::graphics::dx12
{

void InterfaceDX12::Initialize(const GraphicsSpecification& specs)
{
	DXCREATE_LOGGER();
	DXTRACE("Initializing");

	m_Context.Create();

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
