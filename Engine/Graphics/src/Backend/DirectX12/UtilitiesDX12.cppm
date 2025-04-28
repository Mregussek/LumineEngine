
module;

#include <string>
#include <dxgi1_6.h>

export module UtilitiesDX12;


export namespace lumine::graphics::dx12
{

std::string GetGpuNameStr(const DXGI_ADAPTER_DESC3& adapterDesc);

}
