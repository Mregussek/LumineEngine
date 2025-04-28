
module;

export module BackendInterface;

import FactoryVk;

#if LUMINE_WIN64
	import InterfaceDX12;
#endif


export namespace lumine::graphics
{

class IBackendInterface
{
public:

	virtual ~IBackendInterface() = default;

public:

	virtual void Initialize() = 0;
	virtual void Close() = 0;

};


template<typename TConcreteInterface>
class BackendInterface : public IBackendInterface
{
public:

	void Initialize() override { m_Interface.Initialize(); }
	void Close() override { m_Interface.Close(); }

private:

	TConcreteInterface m_Interface{};

};


typedef BackendInterface<vk::FactoryVk> BackedInterfaceVk;

#if LUMINE_WIN64
	typedef BackendInterface<dx12::InterfaceDX12> BackendInterfaceDX12;
#endif

}
