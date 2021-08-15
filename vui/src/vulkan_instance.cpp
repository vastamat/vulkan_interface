#include "vulkan_instance.h"

#include <assert.h>
#include <iostream>
#include <algorithm>
#include <cstring>

static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
    void *pUserData)
{
    switch (messageSeverity)
    {
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
        std::cout << "[Diagnostic] validation layer: " << pCallbackData->pMessage << std::endl;
        break;
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
        std::cout << "[Info] validation layer: " << pCallbackData->pMessage << std::endl;
        break;
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
        std::cout << "[Warning] validation layer: " << pCallbackData->pMessage << std::endl;
        break;
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
        std::cerr << "[Error] validation layer: " << pCallbackData->pMessage << std::endl;
        break;
    }

    return VK_FALSE;
}

static VkResult CreateDebugUtilsMessengerEXT(VkInstance instance,
                                             const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo,
                                             const VkAllocationCallbacks *pAllocator,
                                             VkDebugUtilsMessengerEXT *pDebugMessenger)
{
    auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
    if (func != nullptr)
    {
        return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
    }
    else
    {
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }
}

static void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks *pAllocator)
{
    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
    if (func != nullptr)
    {
        func(instance, debugMessenger, pAllocator);
    }
}

vui::VulkanInstance::VulkanInstance(const std::vector<const char *> &requestedValidationLayers,
                                    const std::vector<const char *> &requestedExtensions)
    : m_VulkanInstance(VK_NULL_HANDLE),
      m_DebugMessenger(VK_NULL_HANDLE)
{
#if VUI_DEBUG
    if (!CheckRequestedLayersAreAvailable(requestedValidationLayers))
    {
        std::cerr << "Requested validation layers not available!" << '\n';
        assert(false);
    }
#endif

    if (!CheckRequestedExtensionsAreAvailable(requestedExtensions))
    {
        std::cerr << "Requested extensions not available!" << '\n';
        assert(false);
    }

    VkApplicationInfo appInfo = GetVulkanAppInfo();

    CreateVulkanInstanceInternal(appInfo, requestedValidationLayers, requestedExtensions);

#if VUI_DEBUG
    SetupDebugMessenger();
#endif
}

vui::VulkanInstance::~VulkanInstance()
{
    if (m_VulkanInstance)
    {
#if VUI_DEBUG
        DestroyDebugUtilsMessengerEXT(m_VulkanInstance, m_DebugMessenger, nullptr);
#endif
        vkDestroyInstance(m_VulkanInstance, nullptr);
    }
}

bool vui::VulkanInstance::CheckRequestedLayersAreAvailable(const std::vector<const char *> &requestedValidationLayers) const
{
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    bool allLayersAreSupported = true;

    for (auto &&validationLayerName : requestedValidationLayers)
    {
        auto pos = std::find_if(std::begin(availableLayers), std::end(availableLayers),
                                [validationLayerName](const VkLayerProperties &vkLayer)
                                {
                                    return strcmp(validationLayerName, vkLayer.layerName) == 0;
                                });

        if (pos == std::end(availableLayers))
        {
            std::cout << "Required validation layer [ " << validationLayerName << " ] is not available." << '\n';
            allLayersAreSupported = false;
        }
    }

    return allLayersAreSupported;
}

bool vui::VulkanInstance::CheckRequestedExtensionsAreAvailable(const std::vector<const char *> &requestedExtensions) const
{
    uint32_t vulkanExtensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &vulkanExtensionCount, nullptr);
    std::vector<VkExtensionProperties> vulkanExtensions(vulkanExtensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &vulkanExtensionCount, vulkanExtensions.data());

    bool allExtensionsAreAvailable = true;

    for (auto &&requiredExtension : requestedExtensions)
    {
        auto pos = std::find_if(std::begin(vulkanExtensions), std::end(vulkanExtensions),
                                [requiredExtension](const VkExtensionProperties &vkExtension)
                                { return strcmp(requiredExtension, vkExtension.extensionName) == 0; });

        if (pos == std::end(vulkanExtensions))
        {
            std::cout << "Required extension [ " << requiredExtension << " ] is missing." << '\n';
            allExtensionsAreAvailable = false;
        }
    }

    return allExtensionsAreAvailable;
}

VkApplicationInfo vui::VulkanInstance::GetVulkanAppInfo() const
{
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Vulkan App";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    return appInfo;
}

void vui::VulkanInstance::CreateVulkanInstanceInternal(const VkApplicationInfo &appInfo,
                                                       const std::vector<const char *> &requestedValidationLayers,
                                                       const std::vector<const char *> &requestedExtensions)
{
    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    createInfo.enabledExtensionCount = static_cast<uint32_t>(requestedExtensions.size());
    createInfo.ppEnabledExtensionNames = requestedExtensions.data();

#if VUI_DEBUG
    createInfo.enabledLayerCount = static_cast<uint32_t>(requestedValidationLayers.size());
    createInfo.ppEnabledLayerNames = requestedValidationLayers.data();

    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo = GetDebugMessengerCreateInfo();
    createInfo.pNext = static_cast<VkDebugUtilsMessengerCreateInfoEXT *>(&debugCreateInfo);
#else
    createInfo.enabledLayerCount = 0;
    createInfo.pNext = nullptr;
#endif

    VkResult result = vkCreateInstance(&createInfo, nullptr, &m_VulkanInstance);
    assert(result == VK_SUCCESS);
}

VkDebugUtilsMessengerCreateInfoEXT vui::VulkanInstance::GetDebugMessengerCreateInfo() const
{
    VkDebugUtilsMessengerCreateInfoEXT createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;

    createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
                                 VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                                 VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;

    createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                             VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                             VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;

    createInfo.pfnUserCallback = DebugCallback;

    return createInfo;
}

void vui::VulkanInstance::SetupDebugMessenger()
{
    VkDebugUtilsMessengerCreateInfoEXT createInfo = GetDebugMessengerCreateInfo();
    createInfo.pUserData = nullptr; // Optional

    if (CreateDebugUtilsMessengerEXT(m_VulkanInstance, &createInfo, nullptr, &m_DebugMessenger) != VK_SUCCESS)
    {
        std::cerr << "failed to set up debug messenger!!" << '\n';
        assert(false);
    }
}