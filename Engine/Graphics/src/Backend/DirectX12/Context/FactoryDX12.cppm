
module;

#include "Types.h"
#include <wrl/client.h>
#include <dxgi1_6.h>

export module FactoryDX12;

import DebugDX12;


export namespace lumine::graphics::dx12
{

class FactoryDX12
{
	template<typename T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public:

	void Create();

	[[nodiscard]] const ComPtr<IDXGIFactory7>& Handle() const { return m_Factory; }

private:

	void CreateFactory();
	void SelectAdapter();

private:

	ComPtr<IDXGIFactory7> m_Factory{ nullptr };
	ComPtr<IDXGIAdapter4> m_pAdapter{ nullptr };

#if LUMINE_DEBUG
	DebugDX12 m_Debug{};
#endif

};

}
