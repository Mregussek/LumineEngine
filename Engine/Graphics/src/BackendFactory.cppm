
module;

export module BackendFactory;

import FactoryVk;

#if LUMINE_WIN64
	import FactoryDX12;
#endif


export namespace lumine::graphics
{

class IBackendFactory
{
public:

	virtual ~IBackendFactory() = default;

public:

	virtual void Initialize() = 0;
	virtual void Close() = 0;

};


template<typename TConcreteFactory>
class BackendFactory : public IBackendFactory
{
public:

	void Initialize() override { m_Factory.Initialize(); }
	void Close() override { m_Factory.Close(); }

private:

	TConcreteFactory m_Factory{};

};


typedef BackendFactory<vk::FactoryVk> BackedFactoryVk;

#if LUMINE_WIN64
	typedef BackendFactory<dx12::FactoryDX12> BackendFactoryDX12;
#endif

}
