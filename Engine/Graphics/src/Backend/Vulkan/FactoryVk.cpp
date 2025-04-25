
module;

#include "LoggerVk.h"

module FactoryVk;


namespace lumine::graphics::vk
{

FactoryVk::~FactoryVk()
{
	Close();
}

void FactoryVk::Initialize()
{
	VKCREATE_LOGGER();

	VKTRACE("Initialized");
}

void FactoryVk::Close()
{
	VKTRACE("Closed");
}

}
