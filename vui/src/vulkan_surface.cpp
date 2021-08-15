#include "vulkan_surface.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <assert.h>

vui::VulkanSurface::VulkanSurface(const VulkanInstance &vulkanInstance, const Window &window)
    : m_Surface(VK_NULL_HANDLE),
      m_VulkanInstanceRef(vulkanInstance)
{
    VkResult result = glfwCreateWindowSurface(m_VulkanInstanceRef.GetInstanceHandle(), window.GetWindowHandle(), nullptr, &m_Surface);
    assert(result == VK_SUCCESS);
}

vui::VulkanSurface::~VulkanSurface()
{
    vkDestroySurfaceKHR(m_VulkanInstanceRef.GetInstanceHandle(), m_Surface, nullptr);
}
