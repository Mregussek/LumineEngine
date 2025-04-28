
module;

#include <string>
#include <dxgi1_6.h>
#include <d3d12.h>

export module UtilitiesDX12;


export namespace lumine::graphics::dx12
{

constexpr D3D_FEATURE_LEVEL L_D3D12_MIN_FEATURE_LEVEL = D3D_FEATURE_LEVEL_12_2;

std::string GetGpuNameStr(const DXGI_ADAPTER_DESC3& adapterDesc);

}
