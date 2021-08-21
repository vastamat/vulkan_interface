#pragma once

#include "vulkan_instance.h"
#include "vulkan_surface.h"

#include <optional>

namespace vui
{
    struct QueueFamilyIndices
    {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;

        bool isComplete()
        {
            return graphicsFamily.has_value() && presentFamily.has_value();
        }
    };

    class VulkanDevice
    {
    public:
        VulkanDevice(const VulkanInstance &vulkanInstance,
                     const VulkanSurface &surface,
                     const std::vector<const char *> &requestedValidationLayers,
                     const std::vector<const char *> &requestedExtensions);
        ~VulkanDevice();

        VulkanDevice(const VulkanDevice &other) = delete;
        VulkanDevice(VulkanDevice &&other) noexcept = delete;

        VulkanDevice &operator=(const VulkanDevice &other) = delete;
        VulkanDevice &operator=(VulkanDevice &&other) noexcept = delete;

        VkPhysicalDevice GetPhysicalDeviceHandle() const { return m_PhysicalGPU; }
        VkDevice GetLogicalDeviceHandle() const { return m_LogicalDevice; }
        QueueFamilyIndices GetQueueFamilyIndices() const { return m_QueueFamiliesIndices; }

    private:
        std::vector<VkPhysicalDevice>
        GetAllPhysicalDevices(const VulkanInstance &vulkankInstance) const;
        VkPhysicalDevice GetBestDeviceCandidate(const std::vector<VkPhysicalDevice> &physicalGPUs,
                                                const VulkanSurface &surface,
                                                const std::vector<const char *> &requestedExtensions) const;
        int RateDeviceSuitability(VkPhysicalDevice physicalDevice,
                                  const VulkanSurface &surface,
                                  const std::vector<const char *> &requestedExtensions) const;
        QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice physicalDevice, const VulkanSurface &surface) const;
        bool CheckDeviceExtensionsAvailability(VkPhysicalDevice physicalDevice, const std::vector<const char *> &requestedExtensions) const;
        std::vector<VkDeviceQueueCreateInfo> GetQueuesCreateInfo() const;
        VkPhysicalDeviceFeatures GetDeviceFeatures() const;
        void CreateLogicalDeviceInternal(const std::vector<VkDeviceQueueCreateInfo> &queuesCreateInfo,
                                         const VkPhysicalDeviceFeatures &physicalDeviceFeatures,
                                         const std::vector<const char *> &requestedValidationLayers,
                                         const std::vector<const char *> &requestedExtensions);

    private:
        VkPhysicalDevice m_PhysicalGPU;
        VkDevice m_LogicalDevice;
        VkQueue m_GraphicsQueue;
        VkQueue m_PresentQueue;

        QueueFamilyIndices m_QueueFamiliesIndices;
    };
}