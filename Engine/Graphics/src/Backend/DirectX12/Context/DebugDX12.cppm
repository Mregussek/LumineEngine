
module;

#include <wrl/client.h>
#include <d3d12.h>

export module DebugDX12;


export namespace lumine::graphics::dx12
{

class DebugFactoryDX12
{
	template<typename T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public:

	void Enable(UINT& dxgiFactoryFlags);

	void Destroy();

private:

	ComPtr<ID3D12Debug6> m_DebugController{ nullptr };
	bool m_bEnabled{ false };

};


class DebugDeviceDX12
{
	template<typename T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public:

	void Enable(const ComPtr<ID3D12Device>& pDevice);

	void Destroy();

private:

	ComPtr<ID3D12DebugDevice2> m_DebugDevice{ nullptr };
	bool m_bEnabled{ false };

};

}
