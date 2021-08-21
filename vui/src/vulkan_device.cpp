#include "vulkan_device.h"

#include "vulkan_swapchain.h"

#include <assert.h>
#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <cstring>

vui::VulkanDevice::VulkanDevice(const VulkanInstance &vulkanInstance,
                                const VulkanSurface &surface,
                                const std::vector<const char *> &requestedValidationLayers,
                                const std::vector<const char *> &requestedExtensions)
    : m_PhysicalGPU(VK_NULL_HANDLE),
      m_LogicalDevice(VK_NULL_HANDLE),
      m_GraphicsQueue(VK_NULL_HANDLE),
      m_PresentQueue(VK_NULL_HANDLE),
      m_QueueFamiliesIndices()
{
    std::vector<VkPhysicalDevice> physicalGPUs = GetAllPhysicalDevices(vulkanInstance);
    m_PhysicalGPU = GetBestDeviceCandidate(physicalGPUs, surface, requestedExtensions);
    m_QueueFamiliesIndices = FindQueueFamilies(m_PhysicalGPU, surface);

    std::vector<VkDeviceQueueCreateInfo> queuesCreateInfo = GetQueuesCreateInfo();

    VkPhysicalDeviceFeatures deviceFeatures = GetDeviceFeatures();

    CreateLogicalDeviceInternal(queuesCreateInfo, deviceFeatures, requestedValidationLayers, requestedExtensions);

    vkGetDeviceQueue(m_LogicalDevice, m_QueueFamiliesIndices.graphicsFamily.value(), 0, &m_GraphicsQueue);
    vkGetDeviceQueue(m_LogicalDevice, m_QueueFamiliesIndices.presentFamily.value(), 0, &m_PresentQueue);
}

vui::VulkanDevice::~VulkanDevice()
{
    if (m_LogicalDevice)
    {
        vkDestroyDevice(m_LogicalDevice, nullptr);
    }
}

std::vector<VkPhysicalDevice> vui::VulkanDevice::GetAllPhysicalDevices(const VulkanInstance &vulkanInstance) const
{
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(vulkanInstance.GetInstanceHandle(), &deviceCount, nullptr);

    if (deviceCount == 0)
    {
        std::cerr << "failed to find GPUs with Vulkan support!" << '\n';
        assert(false);
    }

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(vulkanInstance.GetInstanceHandle(), &deviceCount, devices.data());

    return devices;
}

VkPhysicalDevice vui::VulkanDevice::GetBestDeviceCandidate(const std::vector<VkPhysicalDevice> &physicalGPUs,
                                                           const VulkanSurface &surface,
                                                           const std::vector<const char *> &requestedExtensions) const
{
    std::multimap<int, VkPhysicalDevice> candidates;

    for (const auto &device : physicalGPUs)
    {
        int score = RateDeviceSuitability(device, surface, requestedExtensions);
        candidates.insert(std::make_pair(score, device));
    }

    auto bestCandidate = candidates.rbegin();
    // Check if the best candidate is suitable at all
    if (bestCandidate->first > 0)
    {
        return bestCandidate->second;
    }
    else
    {
        std::cerr << "failed to find a suitable GPU!" << '\n';
        assert(false);
    }
}

int vui::VulkanDevice::RateDeviceSuitability(VkPhysicalDevice physicalDevice,
                                             const VulkanSurface &surface,
                                             const std::vector<const char *> &requestedExtensions) const
{
    VkPhysicalDeviceProperties deviceProperties;
    vkGetPhysicalDeviceProperties(physicalDevice, &deviceProperties);

    VkPhysicalDeviceFeatures deviceFeatures;
    vkGetPhysicalDeviceFeatures(physicalDevice, &deviceFeatures);

    // Find the available queue families for this gpu
    QueueFamilyIndices indices = FindQueueFamilies(physicalDevice, surface);

    bool supportsRequiredExtensions = CheckDeviceExtensionsAvailability(physicalDevice, requestedExtensions);

    bool swapChainAdequate = false;
    if (supportsRequiredExtensions)
    {
        SwapChainSupportDetails swapChainSupport(physicalDevice, surface.GetSurfaceHandle());
        swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
    }
    
    // Application can't function without geometry shaders or missing queue families/extensions/swapchain support
    if (!deviceFeatures.geometryShader || !indices.isComplete() || !supportsRequiredExtensions || !swapChainAdequate)
    {
        return 0;
    }

    int score = 0;

    // Discrete GPUs have a significant performance advantage
    if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
    {
        score += 1000;
    }

    // explicitly prefer a physical device that supports drawing and presentation in the same queue for improved performance
    if (indices.graphicsFamily == indices.presentFamily)
    {
        score += 1000;
    }

    // Maximum possible size of textures affects graphics quality
    score += deviceProperties.limits.maxImageDimension2D;

    return score;
}

vui::QueueFamilyIndices vui::VulkanDevice::FindQueueFamilies(VkPhysicalDevice physicalDevice, const VulkanSurface &surface) const
{
    QueueFamilyIndices indices;

    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilies.data());

    int i = 0;
    for (const auto &queueFamily : queueFamilies)
    {
        if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
        {
            indices.graphicsFamily = i;
        }

        VkBool32 presentSupport = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, i, surface.GetSurfaceHandle(), &presentSupport);

        if (presentSupport)
        {
            indices.presentFamily = i;
        }

        if (indices.isComplete())
        {
            break;
        }

        i++;
    }

    return indices;
}

bool vui::VulkanDevice::CheckDeviceExtensionsAvailability(VkPhysicalDevice physicalDevice, const std::vector<const char *> &requestedExtensions) const
{
    uint32_t extensionCount;
    vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, nullptr);

    std::vector<VkExtensionProperties> availableExtensions(extensionCount);
    vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, availableExtensions.data());

    bool allFound = true;

    for (auto &&requestedExtension : requestedExtensions)
    {
        auto pos = std::find_if(std::begin(availableExtensions), std::end(availableExtensions),
                                [requestedExtension](const VkExtensionProperties &availableExtensionProperty)
                                {
                                    return strcmp(requestedExtension, availableExtensionProperty.extensionName);
                                });

        if (pos == std::end(availableExtensions))
        {
            std::cerr << "Unable to find required device extension " << requestedExtension << " \n";
            allFound = false;
        }
    }

    return allFound;
}

std::vector<VkDeviceQueueCreateInfo> vui::VulkanDevice::GetQueuesCreateInfo() const
{
    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    std::set<uint32_t> uniqueQueueFamilies = {m_QueueFamiliesIndices.graphicsFamily.value(),
                                              m_QueueFamiliesIndices.presentFamily.value()};

    float queuePriorities[1] = {0.0};

    for (uint32_t queueFamily : uniqueQueueFamilies)
    {
        VkDeviceQueueCreateInfo queueCreateInfo{};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = queueFamily;
        queueCreateInfo.queueCount = 1;
        queueCreateInfo.pQueuePriorities = queuePriorities;
        queueCreateInfo.pNext = nullptr;
        queueCreateInfos.push_back(queueCreateInfo);
    }

    return queueCreateInfos;
}

VkPhysicalDeviceFeatures vui::VulkanDevice::GetDeviceFeatures() const
{
    VkPhysicalDeviceFeatures deviceFeatures{};
    return deviceFeatures;
}

void vui::VulkanDevice::CreateLogicalDeviceInternal(const std::vector<VkDeviceQueueCreateInfo> &queuesCreateInfo,
                                                    const VkPhysicalDeviceFeatures &physicalDeviceFeatures,
                                                    const std::vector<const char *> &requestedValidationLayers,
                                                    const std::vector<const char *> &requestedExtensions)
{
    VkDeviceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

    createInfo.queueCreateInfoCount = static_cast<uint32_t>(queuesCreateInfo.size());
    createInfo.pQueueCreateInfos = queuesCreateInfo.data();

    createInfo.pEnabledFeatures = &physicalDeviceFeatures;

    createInfo.enabledExtensionCount = static_cast<uint32_t>(requestedExtensions.size());
    createInfo.ppEnabledExtensionNames = requestedExtensions.data();

#if VUI_DEBUG
    createInfo.enabledLayerCount = static_cast<uint32_t>(requestedValidationLayers.size());
    createInfo.ppEnabledLayerNames = requestedValidationLayers.data();
#else
    createInfo.enabledLayerCount = 0;
#endif

    VkResult result = vkCreateDevice(m_PhysicalGPU, &createInfo, nullptr, &m_LogicalDevice);
    assert(result == VK_SUCCESS);
}
