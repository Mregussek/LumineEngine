
module;

#include "LoggerDX12.h"

module InterfaceDX12;


namespace lumine::graphics::dx12
{

InterfaceDX12::~InterfaceDX12()
{
	Close();
}

void InterfaceDX12::Initialize()
{
	DXCREATE_LOGGER();
	DXTRACE("Initializing");

	m_Context.Create();

	DXDEBUG("Initialized");
}

void InterfaceDX12::Close()
{
	DXDEBUG("Closed");
}

}
