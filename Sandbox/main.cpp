
#if LUMINE_USE_DIRECTX12
    #define LUMINE_USE_DIRECTX12 1
#endif
#if LUMINE_USE_VULKAN
    #define LUMINE_USE_DIRECTX12 0
#endif

import GraphicsFactory;
import VulkanFactory;
import DX12Factory;
#include <memory>

using namespace lumine::graphics;


constexpr std::unique_ptr<GraphicsFactory> CreateFactory()
{
    if constexpr (LUMINE_USE_DIRECTX12)
    {
        return std::make_unique<DX12Factory>();
    }

    // Assume we want to use Vulkan | LUMINE_USE_VULKAN
    return std::make_unique<VulkanFactory>();
}

int main()
{
    std::unique_ptr<GraphicsFactory> pGraphicsFactory = CreateFactory();
    pGraphicsFactory->Initialize();
}
