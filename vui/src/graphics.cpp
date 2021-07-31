#include "graphics.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <algorithm>
#include <assert.h>
#include <vector>
#include <iostream>
#include <cstring>

static vui::Graphics *s_GraphicsInstance = nullptr;

vui::Graphics::Graphics()
{
    assert(s_GraphicsInstance == nullptr);
    s_GraphicsInstance = this;

    bool success = glfwInit();
    assert(success);

    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Vulkan App";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    uint32_t glfwExtensionCount = 0;
    const char **glfwExtensions;

    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    createInfo.enabledExtensionCount = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;
    createInfo.enabledLayerCount = 0;

    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
    std::vector<VkExtensionProperties> extensions(extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

    for (size_t i = 0; i < glfwExtensionCount; i++)
    {
        auto pos = std::find_if(std::begin(extensions), std::end(extensions), [glfwExtension = glfwExtensions[i]](const VkExtensionProperties &vkExtension)
                                { return strcmp(glfwExtension, vkExtension.extensionName) == 0; });

        if (pos == std::end(extensions))
        {
            std::cout << "Required GLFW extension [ " << glfwExtensions[i] << " ] is missing."<< '\n';
        }
    }

    std::cout << "available extensions:\n";
    for (const auto &extension : extensions)
    {
        std::cout << '\t' << extension.extensionName << '\n';
    }

    std::cout << "glfw required extensions:\n";
    for (size_t i = 0; i < glfwExtensionCount; i++)
    {
        std::cout << '\t' << glfwExtensions[i] << '\n';
    }

    VkResult result = vkCreateInstance(&createInfo, nullptr, &m_VulkanInstance);
    assert(result == VK_SUCCESS);
}

vui::Graphics::~Graphics()
{
    vkDestroyInstance(m_VulkanInstance, nullptr);
    glfwTerminate();
    s_GraphicsInstance = nullptr;
}
