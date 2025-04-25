
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

	virtual void Initialize() { }
	virtual void Close() { }

};


template<typename T>
class TBackendFactory : public BackendFactory
{
public:

	void Initialize() override { m_Factory.Initialize(); }
	void Close() override { m_Factory.Close(); }

private:

	T m_Factory{};

};


typedef TBackendFactory<vk::FactoryVk> FactoryVk;

#if LUMINE_WIN64
	typedef TBackendFactory<dx12::FactoryDX12> FactoryDX12;
#endif

}
