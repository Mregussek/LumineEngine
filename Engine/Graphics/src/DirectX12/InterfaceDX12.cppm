
module;

export module InterfaceDX12;

import GraphicsSpecification;
import ContextDX12;


export namespace lumine::graphics::dx12
{

class InterfaceDX12 {
public:

	void Initialize(const GraphicsSpecification& specs);
	void Close();

private:

	ContextDX12 m_Context{};
	bool m_bInitialized{ false };

};

}
