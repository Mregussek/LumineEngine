
module;

#include <wrl/client.h>
#include <d3d12.h>

export module DebugDX12;


export namespace lumine::graphics::dx12
{

class DebugDX12
{
	template<typename T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public:

	void Enable(UINT& dxgiFactoryFlags);

private:

	ComPtr<ID3D12Debug6> m_DebugController{ nullptr };
	ComPtr<ID3D12DebugDevice2> m_DebugDevice{ nullptr };

};

}
