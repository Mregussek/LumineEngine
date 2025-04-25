
module;

export module FactoryDX12;

import ContextDX12;


export namespace lumine::graphics::dx12
{

class FactoryDX12 {
public:

    ~FactoryDX12();

public:

    void Initialize();
    void Close();

private:

    ContextDX12 m_Context{};

};

}
