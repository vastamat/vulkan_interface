#pragma once

#include "vulkan_instance.h"
#include "window.h"

namespace vui
{
    class VulkanSurface
    {
    public:
        VulkanSurface(const VulkanInstance &vulkanInstance, const Window &window);
        ~VulkanSurface();

        VulkanSurface(const VulkanSurface &other) = delete;
        VulkanSurface(VulkanSurface &&other) noexcept = delete;

        VulkanSurface &operator=(const VulkanSurface &other) = delete;
        VulkanSurface &operator=(VulkanSurface &&other) noexcept = delete;

        VkSurfaceKHR GetSurfaceHandle() const { return m_Surface; }

    private:
        VkSurfaceKHR m_Surface;

        const VulkanInstance &m_VulkanInstanceRef;
    };
}