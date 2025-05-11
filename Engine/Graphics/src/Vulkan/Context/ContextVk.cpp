
module;

#include <volk.h>
#include "LoggerVk.h"

module ContextVk;


namespace lumine::graphics::vk
{

void ContextVk::Create()
{
	VkResult result = volkInitialize();
	VKTRACE("Created");
}

void ContextVk::Destroy()
{
	VKTRACE("Destroyed");
}

}
