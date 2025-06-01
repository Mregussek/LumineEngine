
module;

#include <dxgi1_6.h>

export module SpecificationDX12;

import GraphicsSpecification;


export namespace lumine::graphics::dx12
{

class SpecificationAdapterDX12
{
public:

	[[nodiscard]] static DXGI_FORMAT Format(EFormat format);

};

}
