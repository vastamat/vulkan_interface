#include "vulkan_swapchain.h"

#include <assert.h>
#include <algorithm>
#include <limits>

vui::SwapChainSupportDetails::SwapChainSupportDetails(VkPhysicalDevice device, VkSurfaceKHR surface)
    : capabilities(),
      formats(),
      presentModes()
{
    // capabilities
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &capabilities);

    // formats
    uint32_t formatCount;
    vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);

    if (formatCount != 0)
    {
        formats.resize(formatCount);
        vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, formats.data());
    }

    // presentation modes
    uint32_t presentModeCount;
    vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, nullptr);

    if (presentModeCount != 0)
    {
        presentModes.resize(presentModeCount);
        vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, presentModes.data());
    }
}

vui::VulkanSwapChain::VulkanSwapChain(const VulkanDevice &vulkanDevice,
                                      const VulkanSurface &vulkanSurface,
                                      const std::pair<int32_t, int32_t> &framebufferSize)
    : m_VulkanDeviceRef(vulkanDevice),
      m_Format(),
      m_PresentationMode(),
      m_SwapExtent(),
      m_SwapChain(VK_NULL_HANDLE),
      m_SwapChainImages()
{
    SwapChainSupportDetails swapChainSupport(vulkanDevice.GetPhysicalDeviceHandle(), vulkanSurface.GetSurfaceHandle());

    m_Format = ChooseSwapSurfaceFormat(swapChainSupport.formats);
    m_PresentationMode = ChooseSwapPresentMode(swapChainSupport.presentModes);
    m_SwapExtent = ChooseSwapExtent(swapChainSupport.capabilities, framebufferSize);

    CreateSwapChainInternal(swapChainSupport.capabilities, vulkanDevice, vulkanSurface);
    CreateSwapChainImages(vulkanDevice);
}

vui::VulkanSwapChain::~VulkanSwapChain()
{
    vkDestroySwapchainKHR(m_VulkanDeviceRef.GetLogicalDeviceHandle(), m_SwapChain, nullptr);
}

VkSurfaceFormatKHR vui::VulkanSwapChain::ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats) const
{
    for (auto &&availableFormat : availableFormats)
    {
        if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
        {
            return availableFormat;
        }
    }

    return availableFormats[0];
}

VkPresentModeKHR vui::VulkanSwapChain::ChooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes) const
{
    for (auto &&availablePresentMode : availablePresentModes)
    {
        if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
        {
            return availablePresentMode;
        }
    }

    return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D vui::VulkanSwapChain::ChooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities,
                                                  const std::pair<int32_t, int32_t> &framebufferSize) const
{
    if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max())
    {
        return capabilities.currentExtent;
    }
    else
    {
        auto [framebufferWidth, framebufferHeight] = framebufferSize;
        VkExtent2D actualExtent = {static_cast<uint32_t>(framebufferWidth), static_cast<uint32_t>(framebufferHeight)};

        actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
        actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

        return actualExtent;
    }
}

void vui::VulkanSwapChain::CreateSwapChainInternal(VkSurfaceCapabilitiesKHR capabilities,
                                                   const VulkanDevice &vulkanDevice,
                                                   const VulkanSurface &vulkanSurface)
{
    uint32_t imageCount = capabilities.minImageCount + 1;

    if (capabilities.maxImageCount > 0 && imageCount > capabilities.maxImageCount)
    {
        imageCount = capabilities.maxImageCount;
    }

    VkSwapchainCreateInfoKHR createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.surface = vulkanSurface.GetSurfaceHandle();
    createInfo.minImageCount = imageCount;
    createInfo.imageFormat = m_Format.format;
    createInfo.imageColorSpace = m_Format.colorSpace;
    createInfo.imageExtent = m_SwapExtent;
    createInfo.imageArrayLayers = 1;
    createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

    QueueFamilyIndices queueIndices = vulkanDevice.GetQueueFamilyIndices();
    uint32_t queueFamilyIndices[] = {queueIndices.graphicsFamily.value(), queueIndices.presentFamily.value()};

    if (queueIndices.graphicsFamily != queueIndices.presentFamily)
    {
        createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        createInfo.queueFamilyIndexCount = 2;
        createInfo.pQueueFamilyIndices = queueFamilyIndices;
    }
    else
    {
        createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        createInfo.queueFamilyIndexCount = 0;     // Optional
        createInfo.pQueueFamilyIndices = nullptr; // Optional
    }

    createInfo.preTransform = capabilities.currentTransform;
    createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    createInfo.presentMode = m_PresentationMode;
    createInfo.clipped = VK_TRUE;
    createInfo.oldSwapchain = VK_NULL_HANDLE;

    VkResult result = vkCreateSwapchainKHR(vulkanDevice.GetLogicalDeviceHandle(), &createInfo, nullptr, &m_SwapChain);
    assert(result == VK_SUCCESS);
}
void vui::VulkanSwapChain::CreateSwapChainImages(const VulkanDevice &vulkanDevice)
{
    uint32_t swapChainImageCount = 0;

    vkGetSwapchainImagesKHR(vulkanDevice.GetLogicalDeviceHandle(), m_SwapChain, &swapChainImageCount, nullptr);
    m_SwapChainImages.resize(swapChainImageCount);
    vkGetSwapchainImagesKHR(vulkanDevice.GetLogicalDeviceHandle(), m_SwapChain, &swapChainImageCount, m_SwapChainImages.data());
}
