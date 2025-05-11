
module;

#include <string>
#include <dxgi1_6.h>

module UtilitiesDX12;


namespace lumine::graphics::dx12
{

std::string GetGpuNameStr(const DXGI_ADAPTER_DESC3& adapterDesc)
{
	std::wstring wstr(adapterDesc.Description);
	return std::string(wstr.begin(), wstr.end());
}

}
