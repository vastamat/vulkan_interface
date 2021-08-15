#pragma once

#include <vulkan/vulkan.h>
#include <vector>

namespace vui
{
    class VulkanInstance
    {
    public:
        VulkanInstance(const std::vector<const char *> &requestedValidationLayers, const std::vector<const char *> &requestedExtensions);
        ~VulkanInstance();

        VulkanInstance(const VulkanInstance &other) = delete;
        VulkanInstance(VulkanInstance &&other) noexcept = delete;

        VulkanInstance &operator=(const VulkanInstance &other) = delete;
        VulkanInstance &operator=(VulkanInstance &&other) noexcept = delete;

        VkInstance GetInstanceHandle() const { return m_VulkanInstance; }

    private:
        bool CheckRequestedLayersAreAvailable(const std::vector<const char *> &requestedValidationLayers) const;
        bool CheckRequestedExtensionsAreAvailable(const std::vector<const char *> &requestedExtensions) const;
        VkApplicationInfo GetVulkanAppInfo() const;
        void CreateVulkanInstanceInternal(const VkApplicationInfo &appInfo,
                                          const std::vector<const char *> &requestedValidationLayers,
                                          const std::vector<const char *> &requestedExtensions);
        VkDebugUtilsMessengerCreateInfoEXT GetDebugMessengerCreateInfo() const;
        void SetupDebugMessenger();

    private:
        VkInstance m_VulkanInstance;
        VkDebugUtilsMessengerEXT m_DebugMessenger;
    };
}