
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
	GTRACE("Initialized");
}

void VulkanFactory::Close()
{
	GTRACE("Closed");
}

}
