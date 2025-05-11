
module;

#define VOLK_IMPLEMENTATION
#include <volk.h>

export module ContextVk;


export namespace lumine::graphics::vk
{

class ContextVk
{
public:

	void Create();
	void Destroy();

};

}
