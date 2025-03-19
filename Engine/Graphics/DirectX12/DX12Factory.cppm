
module;

import GraphicsFactory;

export module DX12Factory;


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
