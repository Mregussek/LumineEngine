
module;

#include "LoggerDX12.h"
#include "Types.h"
#include <wrl/client.h>
#include <dxgi1_6.h>
#include <d3d12.h>
#include <map>

module AdapterSelectorDX12;

import UtilitiesDX12;


namespace lumine::graphics::dx12
{

static u32 GetScore(IDXGIAdapter4* pAdapter)
{
	u32 score{ 0 };

	DXGI_ADAPTER_DESC3 desc;
	pAdapter->GetDesc3(&desc);
	const std::string gpuName = GetGpuNameStr(desc);

	if (desc.Flags & DXGI_ADAPTER_FLAG3_SOFTWARE)
	{
		DXTRACE("Skipping software adapter {}; Score: {}", gpuName, score);
		return score;
	}

	D3D_FEATURE_LEVEL minVersion = D3D_FEATURE_LEVEL_12_2;
	bool bSupportsD3D12 = D3D12CreateDevice(pAdapter, minVersion, _uuidof(ID3D12Device), nullptr);
	if (not bSupportsD3D12)
	{
		DXTRACE("Skipping adapter {}, which does not support D3D12!", gpuName);
		return score;
	}

	u32 vramMb = static_cast<u32>(desc.DedicatedVideoMemory / 1024 / 1024);
	score += vramMb;

	DXTRACE("Adapter {}; VRAM {}; Score {}", gpuName, vramMb, score);
	return score;
}

Microsoft::WRL::ComPtr<IDXGIAdapter4> AdapterSelectorDX12::Select(const ComPtr<IDXGIFactory7>& pFactoryHandle)
{
	IDXGIAdapter4* pAdapter;
	u32 adapterIndex = 0;

	std::multimap<u32, u32> ratings;
	while (pFactoryHandle->EnumAdapterByGpuPreference(adapterIndex, DXGI_GPU_PREFERENCE_UNSPECIFIED, IID_PPV_ARGS(&pAdapter)) != DXGI_ERROR_NOT_FOUND)
	{
		ratings.insert(std::make_pair(GetScore(pAdapter), adapterIndex));
		adapterIndex++;
	}

	u32 selectedAdapter = ratings.rbegin()->second;
	HRESULT hr = pFactoryHandle->EnumAdapterByGpuPreference(selectedAdapter, DXGI_GPU_PREFERENCE_UNSPECIFIED, IID_PPV_ARGS(&pAdapter));
	DXASSERT(hr);

	return pAdapter;
}

}
