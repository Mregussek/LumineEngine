
module;

#include <wrl/client.h>
#include <dxgi1_6.h>

export module AdapterSelectorDX12;


export namespace lumine::graphics::dx12
{

class AdapterSelectorDX12
{
	template<typename T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public:

	static ComPtr<IDXGIAdapter4> Select(const ComPtr<IDXGIFactory7>& pFactoryHandle);

};

}
