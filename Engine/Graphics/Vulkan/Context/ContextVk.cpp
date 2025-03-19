
module;

#include <volk.h>
#include "GLogger.h"

module ContextVk;


namespace lumine::graphics
{

void ContextVk::Create()
{
	VkResult result = volkInitialize();
	GTRACE("Created");
}

void ContextVk::Destroy()
{
	GTRACE("Destroyed");
}

}
