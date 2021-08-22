#pragma once

#include "vulkan_device.h"
#include "vulkan_surface.h"
#include "vulkan_texture2D.h"

#include <vector>

namespace vui
{
    struct SwapChainSupportDetails
    {
        SwapChainSupportDetails(VkPhysicalDevice device, VkSurfaceKHR surface);

        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };

    class VulkanSwapChain
    {
    public:
        VulkanSwapChain(const VulkanDevice &vulkanDevice,
                        const VulkanSurface &vulkanSurface,
                        const std::pair<int32_t, int32_t> &framebufferSize);
        ~VulkanSwapChain();

        VulkanSwapChain(const VulkanSwapChain &other) = delete;
        VulkanSwapChain(VulkanSwapChain &&other) noexcept = delete;

        VulkanSwapChain &operator=(const VulkanSwapChain &other) = delete;
        VulkanSwapChain &operator=(VulkanSwapChain &&other) noexcept = delete;

    private:
        VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats) const;
        VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes) const;
        VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities, const std::pair<int32_t, int32_t> &framebufferSize) const;
        void CreateSwapChainInternal(VkSurfaceCapabilitiesKHR capabilities, const VulkanSurface &vulkanSurface);
        void CreateSwapChainImages();
        void CreateSwapChainTextures();

    private:
        const VulkanDevice &m_VulkanDeviceRef;

        VkSurfaceFormatKHR m_Format;
        VkPresentModeKHR m_PresentationMode;
        VkExtent2D m_SwapExtent;

        VkSwapchainKHR m_SwapChain;
        std::vector<VkImage> m_SwapChainImages;
        std::vector<VulkanTexture2D> m_SwapChainTextures;
    };
}