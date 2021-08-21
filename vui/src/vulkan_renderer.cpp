#include "vulkan_renderer.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

static const std::vector<const char *> s_ValidationLayers = {
    "VK_LAYER_KHRONOS_validation"};

static const std::vector<const char *> s_DeviceExtensionNames = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME};

static std::vector<const char *> GetRequiredInstanceExtensions()
{
    uint32_t glfwExtensionCount = 0;
    const char **glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    std::vector<const char *> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

#if VUI_DEBUG
    extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
#endif

    return extensions;
}

vui::VulkanRenderer::VulkanRenderer(const Window &window)
    : m_VulkanInstance(std::make_unique<VulkanInstance>(s_ValidationLayers, GetRequiredInstanceExtensions())),
      m_Surface(std::make_unique<VulkanSurface>(*m_VulkanInstance, window)),
      m_VulkanDevice(std::make_unique<VulkanDevice>(*m_VulkanInstance, *m_Surface, s_ValidationLayers, s_DeviceExtensionNames)),
      m_SwapChain(std::make_unique<VulkanSwapChain>(*m_VulkanDevice, *m_Surface, window.m_FramebufferSize))
{
}