
module;

import GraphicsFactory;

export module VulkanFactory;


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
