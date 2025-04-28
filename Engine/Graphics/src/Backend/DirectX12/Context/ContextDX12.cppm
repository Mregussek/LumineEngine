
module;

#include "Types.h"
#include <dxgi1_6.h>
#include <d3d12.h>

export module ContextDX12;

import FactoryDX12;
import DeviceDX12;


export namespace lumine::graphics::dx12
{

class ContextDX12
{
public:

	void Create();
	void Destroy();

private:

	FactoryDX12 m_Factory{};
	DeviceDX12 m_Device{};
	bool m_bCreated{ false };

};

}
