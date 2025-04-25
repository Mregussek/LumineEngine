
module;

#include "LoggerDX12.h"

module FactoryDX12;


namespace lumine::graphics::dx12
{

FactoryDX12::~FactoryDX12()
{
	Close();
}

void FactoryDX12::Initialize()
{
	DXCREATE_LOGGER();
	DXTRACE("Initializing");

	m_Context.Create();

	DXDEBUG("Initialized");
}

void FactoryDX12::Close()
{
	DXDEBUG("Closed");
}

}
