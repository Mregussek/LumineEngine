
module;

export module InterfaceDX12;

import ContextDX12;


export namespace lumine::graphics::dx12
{

class InterfaceDX12 {
public:

	void Initialize();
	void Close();

private:

	ContextDX12 m_Context{};
	bool m_bInitialized{ false };

};

}
