
#if LUMINE_USE_DIRECTX12
    #define LUMINE_USE_DIRECTX12 1
#endif
#if LUMINE_USE_VULKAN
    #define LUMINE_USE_DIRECTX12 0
#endif

import ToolsFactory;
import Window;

import GraphicsFactory;
import VulkanFactory;
import DX12Factory;
#include <memory>

using namespace lumine;
using namespace lumine::graphics;


constexpr std::unique_ptr<GraphicsFactory> CreateGraphicsFactory()
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
    std::unique_ptr<ToolsFactory> pToolsFactory = std::make_unique<ToolsFactory>();
    pToolsFactory->Initialize();

    std::unique_ptr<Window> pWindow = pToolsFactory->GetWindow();
    pWindow->Initialize();

    std::unique_ptr<GraphicsFactory> pGraphicsFactory = CreateGraphicsFactory();
    pGraphicsFactory->Initialize();
}
