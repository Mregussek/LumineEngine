
module;

export module BackendFactory;

import FactoryVk;

#if LUMINE_WIN64
	import FactoryDX12;
#endif


export namespace lumine::graphics
{

class BackendFactory
{
public:

	virtual ~BackendFactory() = default;

public:

	virtual void Initialize() = 0;
	virtual void Close() = 0;

};


template<typename TConcreteFactory>
class BackendDerivedFactory : public BackendFactory
{
public:

	void Initialize() override { m_Factory.Initialize(); }
	void Close() override { m_Factory.Close(); }

private:

	TConcreteFactory m_Factory{};

};


typedef BackendDerivedFactory<vk::FactoryVk> FactoryVk;

#if LUMINE_WIN64
	typedef BackendDerivedFactory<dx12::FactoryDX12> FactoryDX12;
#endif

}
