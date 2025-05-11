
module;

#include "LoggerVk.h"

module InterfaceVk;

import GraphicsSpecification;


namespace lumine::graphics::vk
{

void InterfaceVk::Initialize(const GraphicsSpecification& specs)
{
	VKCREATE_LOGGER();

	VKTRACE("Initialized");
}

void InterfaceVk::Close()
{
	VKTRACE("Closed");
}

}
