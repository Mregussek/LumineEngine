
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


struct GraphicsSpecification
{ 
	u32 windowWidth{ 0 };
	u32 windowHeight{ 0 };
	WindowRawHandle windowRawHandle{};
	EFormat swapchainFormat{ EFormat::R8G8B8A8_UNORM };
	u32 swapchainBackBufferCount{ 3 };
};

}
