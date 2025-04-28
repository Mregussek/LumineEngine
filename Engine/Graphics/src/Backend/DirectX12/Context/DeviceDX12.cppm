
module;

#include <wrl/client.h>
#include <dxgi1_6.h>
#include <d3d12.h>

export module DeviceDX12;

import DebugDX12;


export namespace lumine::graphics::dx12
{

class DeviceDX12
{
	template<typename T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public:

	void Create(const ComPtr<IDXGIAdapter4>& pAdapter);
	void Destroy();

private:

	ComPtr<ID3D12Device> m_Device{ nullptr };

#if LUMINE_DEBUG
	DebugDeviceDX12 m_DebugDevice{};
#endif

	bool m_bCreated{ false };

};

}
