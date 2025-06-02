
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

	virtual void Initialize(const GraphicsSpecification& specs) = 0;
	virtual void Close() = 0;

	virtual void Present() = 0;

};


template<typename TConcreteBackend>
class GraphicsBackend : public IGraphicsBackend
{
public:

	void Initialize(const GraphicsSpecification& specs) override { m_Interface.Initialize(specs); }
	void Close() override { m_Interface.Close(); }

	void Present() override { m_Interface.Present(); }

private:

	TConcreteBackend m_Interface{};

};


typedef GraphicsBackend<vk::InterfaceVk> GraphicsBackendVk;

#if LUMINE_WIN64
	typedef GraphicsBackend<dx12::InterfaceDX12> GraphicsBackendDX12;
#endif

}
