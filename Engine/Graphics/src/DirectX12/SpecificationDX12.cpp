
module;

#include <dxgi1_6.h>

module SpecificationDX12;

import GraphicsSpecification;


namespace lumine::graphics::dx12
{

DXGI_FORMAT SpecificationAdapterDX12::Format(EFormat format)
{
	switch (format)
	{
	case EFormat::R8G8B8A8_UNORM:
		return DXGI_FORMAT_R8G8B8A8_UNORM;
	default:
		return DXGI_FORMAT_UNKNOWN;
	}
}

}
