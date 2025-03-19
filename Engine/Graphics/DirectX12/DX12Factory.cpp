
module;

#include "GLogger.h"

module DX12Factory;


namespace lumine::graphics
{

DX12Factory::~DX12Factory()
{
	Close();
}

void DX12Factory::Initialize()
{
	GraphicsFactory::Initialize();
	GTRACE("Initialized");
}

void DX12Factory::Close()
{
	GTRACE("Closed");
	GraphicsFactory::Close();
}

}
