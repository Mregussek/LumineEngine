
module;

#include "Types.h"

export module GraphicsSpecification;

import IWindow;


export namespace lumine::graphics
{

enum class EFormat
{
	Undefined = 0,
	R8G8B8A8_UNORM
};


struct SwapchainSpecification
{
	u32 width{ 0 };
	u32 height{ 0 };
	EFormat format{ EFormat::Undefined };
	u32 backBufferCount{ 2 };
};


struct GraphicsSpecification
{
	SwapchainSpecification swapchain{};
};

}
