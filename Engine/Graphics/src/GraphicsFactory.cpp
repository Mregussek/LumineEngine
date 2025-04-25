
module;

#include "GLogger.h"
#include <memory>

module GraphicsFactory;

import BackendFactory;


namespace lumine::graphics
{

constexpr std::unique_ptr<IBackendFactory> CreateBackendFactory()
{
	if constexpr (LUMINE_WIN64 and LUMINE_USE_DIRECTX12)
	{
		return std::make_unique<BackendFactoryDX12>();
	}
	else
	{
		// Assume we want to use Vulkan | LUMINE_USE_VULKAN
		return std::make_unique<BackedFactoryVk>();
	}
}

}


namespace lumine::graphics
{

GraphicsFactory::~GraphicsFactory()
{
	Close();
}

void GraphicsFactory::Initialize()
{
	GCREATE_LOGGER();

	m_pBackendFactory = CreateBackendFactory();
	m_pBackendFactory->Initialize();

	m_Initialized = true;
	GTRACE("Initialized");
}

void GraphicsFactory::Close()
{
	if (not m_Initialized)
	{
		return;
	}

	m_pBackendFactory->Close();
	m_Initialized = false;
	GTRACE("Closed");
}

}
