
module;

#include "Types.h"
#include "LoggerDX12.h"
#include <wrl/client.h>
#include <dxgi1_6.h>
#include <d3d12.h>
#include <vector>

module FactoryDX12;

import DebugDX12;
import AdapterSelectorDX12;
import UtilitiesDX12;


namespace lumine::graphics::dx12
{

void FactoryDX12::Create()
{
	DXTRACE("Creating");

	CreateFactory();
	SelectAdapter();

	m_bCreated = true;
	DXDEBUG("Created");
}


void FactoryDX12::Destroy()
{
	DXTRACE("Destroying");

	if (m_bCreated)
	{
		m_pAdapter->Release();
		m_pAdapter.Reset();

#if LUMINE_DEBUG
		m_DebugFactory.Destroy();
#endif
		m_Factory->Release();
	}

	m_bCreated = false;
	DXDEBUG("Destroyed");
}


void FactoryDX12::CreateFactory()
{
	UINT dxgiFactoryFlags{ 0 };

#if LUMINE_DEBUG
	m_DebugFactory.Enable(dxgiFactoryFlags);
#endif

	HRESULT hr = CreateDXGIFactory2(dxgiFactoryFlags, IID_PPV_ARGS(m_Factory.ReleaseAndGetAddressOf()));
	DXASSERT(hr);
}


void FactoryDX12::SelectAdapter()
{
	m_pAdapter = AdapterSelectorDX12::Select(m_Factory);

	DXGI_ADAPTER_DESC3 desc;
	m_pAdapter->GetDesc3(&desc);
	std::string gpuName = GetGpuNameStr(desc);
	u32 vramMb = static_cast<u32>(desc.DedicatedVideoMemory / 1024 / 1024);

	DXINFO("Selected Adapter --- {} --- VRAM {} MB", gpuName, vramMb);
}

}