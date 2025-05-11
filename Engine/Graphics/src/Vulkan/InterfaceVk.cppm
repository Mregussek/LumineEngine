
module;

export module InterfaceVk;

import GraphicsSpecification;


export namespace lumine::graphics::vk
{

class InterfaceVk {
public:

	void Initialize(const GraphicsSpecification& specs);
	void Close();

};

}
