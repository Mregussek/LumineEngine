
module;

#include "GLogger.h"

module VulkanFactory;


namespace lumine::graphics
{

VulkanFactory::~VulkanFactory()
{
	Close();
}

void VulkanFactory::Initialize()
{
	GraphicsFactory::Initialize();
	GTRACE("Initialized");
}

void VulkanFactory::Close()
{
	GTRACE("Closed");
	GraphicsFactory::Close();
}

}
