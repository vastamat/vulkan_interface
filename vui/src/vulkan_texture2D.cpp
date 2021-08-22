#include "vulkan_texture2D.h"

#include <assert.h>

vui::VulkanTexture2D::VulkanTexture2D(const VulkanDevice &device, VkImage image, VkFormat format)
    : m_VulkanDeviceRef(device),
      m_ImageView(VK_NULL_HANDLE),
      m_Image(image),
      m_Format(format)
{
    CreateImageViewInternal();
}

vui::VulkanTexture2D::~VulkanTexture2D()
{
    if (m_ImageView)
    {
        vkDestroyImageView(m_VulkanDeviceRef.GetLogicalDeviceHandle(), m_ImageView, nullptr);
    }
}

vui::VulkanTexture2D::VulkanTexture2D(const VulkanTexture2D &other)
    : m_VulkanDeviceRef(other.m_VulkanDeviceRef),
      m_ImageView(VK_NULL_HANDLE),
      m_Image(other.m_Image),
      m_Format(other.m_Format)
{
    CreateImageViewInternal();
}

vui::VulkanTexture2D::VulkanTexture2D(VulkanTexture2D &&other)
    : m_VulkanDeviceRef(other.m_VulkanDeviceRef),
      m_ImageView(other.m_ImageView),
      m_Image(other.m_Image),
      m_Format(other.m_Format)
{
    other.m_ImageView = VK_NULL_HANDLE;
    other.m_Image = VK_NULL_HANDLE;
}

void vui::VulkanTexture2D::CreateImageViewInternal()
{
    VkImageViewCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    createInfo.image = m_Image;

    createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
    createInfo.format = m_Format;

    createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
    createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
    createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
    createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;

    createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    createInfo.subresourceRange.baseMipLevel = 0;
    createInfo.subresourceRange.levelCount = 1;
    createInfo.subresourceRange.baseArrayLayer = 0;
    createInfo.subresourceRange.layerCount = 1;

    VkResult result = vkCreateImageView(m_VulkanDeviceRef.GetLogicalDeviceHandle(), &createInfo, nullptr, &m_ImageView);
    assert(result == VK_SUCCESS);
}
