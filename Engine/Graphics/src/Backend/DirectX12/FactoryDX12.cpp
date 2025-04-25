
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

	DXTRACE("Initialized");
}

void FactoryDX12::Close()
{
	DXTRACE("Closed");
}

}
