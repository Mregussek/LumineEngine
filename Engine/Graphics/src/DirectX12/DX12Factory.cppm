
module;

export module DX12Factory;

import GraphicsFactory;


export namespace lumine::graphics
{

class DX12Factory : public GraphicsFactory {
public:

    ~DX12Factory();

public:

    void Initialize() override;
    void Close() override;

};

}
