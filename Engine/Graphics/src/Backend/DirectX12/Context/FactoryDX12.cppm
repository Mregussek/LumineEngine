
module;

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
	void Destroy();

	[[nodiscard]] const ComPtr<IDXGIFactory7>& HandleFactory() const { return m_Factory; }
	[[nodiscard]] const ComPtr<IDXGIAdapter4>& HandleAdapter() const { return m_pAdapter; }

private:

	void CreateFactory();
	void SelectAdapter();

private:

	ComPtr<IDXGIFactory7> m_Factory{ nullptr };
	ComPtr<IDXGIAdapter4> m_pAdapter{ nullptr };

#if LUMINE_DEBUG
	DebugFactoryDX12 m_DebugFactory{};
#endif

	bool m_bCreated{ false };

};

}
