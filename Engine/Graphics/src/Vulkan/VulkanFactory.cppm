
module;

export module VulkanFactory;

import GraphicsFactory;


export namespace lumine::graphics
{

class VulkanFactory : public GraphicsFactory {
public:

    ~VulkanFactory();

public:

    void Initialize() override;
    void Close() override;

};

}
