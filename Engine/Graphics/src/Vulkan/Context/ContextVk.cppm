
module;

#define VOLK_IMPLEMENTATION
#include <volk.h>

export module ContextVk;


export namespace lumine::graphics
{

class ContextVk
{
public:

	void Create();
	void Destroy();

};

}
