
module;

export module GraphicsBackend;

#include "Types.h"

import GraphicsSpecification;
import InterfaceVk;
#if LUMINE_WIN64
	import InterfaceDX12;
#endif


export namespace lumine::graphics
{

class IGraphicsBackend
{
public:

	virtual ~IGraphicsBackend() = default;

public:

	virtual void Initialize() = 0;
	virtual void Close() = 0;

};


template<typename TConcreteBackend>
class GraphicsBackend : public IGraphicsBackend
{
public:

	void Initialize() override
	{
		GraphicsSpecification specs{};
		m_Interface.Initialize(specs);
	}

	void Close() override
	{
		m_Interface.Close();
	}

private:

	TConcreteBackend m_Interface{};

};


typedef GraphicsBackend<vk::InterfaceVk> GraphicsBackendVk;

#if LUMINE_WIN64
	typedef GraphicsBackend<dx12::InterfaceDX12> GraphicsBackendDX12;
#endif

}
