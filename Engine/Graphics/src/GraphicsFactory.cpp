
module;

#include "GLogger.h"
#include <memory>
import VulkanFactory;
import DX12Factory;

module GraphicsFactory;


namespace lumine::graphics
{

constexpr std::unique_ptr<GraphicsFactory> CreateConcreteFactory()
{
	if constexpr (LUMINE_USE_DIRECTX12)
	{
		return std::make_unique<DX12Factory>();
	}
	else
	{
		// Assume we want to use Vulkan | LUMINE_USE_VULKAN
		return std::make_unique<VulkanFactory>();
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

	m_pConcreteFactory = CreateConcreteFactory();
	m_pConcreteFactory->Initialize();

	m_Initialized = true;
	GTRACE("Initialized");
}

void GraphicsFactory::Close()
{
	if (not m_Initialized)
	{
		return;
	}

	m_pConcreteFactory->Close();
	m_Initialized = false;
	GTRACE("Closed");
}

}
