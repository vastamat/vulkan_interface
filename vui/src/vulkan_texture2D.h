#pragma once

#include "vulkan_device.h"

namespace vui
{
    class VulkanTexture2D
    {
    public:
        VulkanTexture2D(const VulkanDevice &device, VkImage image, VkFormat format);
        ~VulkanTexture2D();

        VulkanTexture2D(const VulkanTexture2D &other);
        VulkanTexture2D(VulkanTexture2D &&other);

        VulkanTexture2D &operator=(const VulkanTexture2D &other) = delete;
        VulkanTexture2D &operator=(VulkanTexture2D &&other) noexcept = delete;

    private:
        void CreateImageViewInternal();

    private:
        const VulkanDevice &m_VulkanDeviceRef;

        VkImageView m_ImageView;
        VkImage m_Image;
        VkFormat m_Format;
    };
} // namespace vui
