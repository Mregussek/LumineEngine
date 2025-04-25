
module;

#include "LoggerDX12.h"
#include <comdef.h>
#include <stdexcept>

export module AssertsDX12;


export namespace lumine::graphics::dx12
{

void AssertDX12(HRESULT hr)
{
	if (FAILED(hr))
	{
		_com_error comErr{ hr };
		std::string errStr = "DX12 Assert: " + std::string{ comErr.ErrorMessage() };
		DXERROR(errStr.c_str());
		throw std::runtime_error(errStr);
	}
}

}
