
module;

#include "Types.h"
#include <wrl/client.h>
#include <dxgi1_6.h>

export module ContextDX12;


export namespace lumine::graphics::dx12
{

class ContextDX12
{

	template<typename T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public:

	ErrorStatus Create();
	void Destroy();

private:

	ComPtr<IDXGIFactory7> m_DxFactory{ nullptr };

};

}
