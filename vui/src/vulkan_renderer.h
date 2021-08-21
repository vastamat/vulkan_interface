#pragma once

#include "vulkan_instance.h"
#include "vulkan_device.h"
#include "vulkan_surface.h"
#include "vulkan_swapchain.h"

#include <memory>

namespace vui
{
    class VulkanRenderer
    {
    public:
        VulkanRenderer(const Window &window);

    private:
        std::unique_ptr<VulkanInstance> m_VulkanInstance;
        std::unique_ptr<VulkanSurface> m_Surface;
        std::unique_ptr<VulkanDevice> m_VulkanDevice;
        std::unique_ptr<VulkanSwapChain> m_SwapChain;
    };
} // namespace vui