#include "graphics.h"

#include <GLFW/glfw3.h>

#include <assert.h>
#include <iostream>
#include <string>

static std::string IntepretGLFWerrorcode(int code)
{
    switch (code)
    {
    case GLFW_NOT_INITIALIZED:
        return "GLFW has not been initialized";
    case GLFW_NO_CURRENT_CONTEXT:
        return "No context is current for this thread";
    case GLFW_INVALID_ENUM:
        return "One of the arguments to the function was an invalid enum value";
    case GLFW_INVALID_VALUE:
        return "One of the arguments to the function was an invalid value";
    case GLFW_OUT_OF_MEMORY:
        return "A memory allocation failed";
    case GLFW_API_UNAVAILABLE:
        return "GLFW could not find support for the requested client API on the "
               "system";
    case GLFW_VERSION_UNAVAILABLE:
        return "The requested OpenGL or OpenGL ES version is not available";
    case GLFW_PLATFORM_ERROR:
        return "A platform - specific error occurred that does not match any of "
               "the more specific categories";
    case GLFW_FORMAT_UNAVAILABLE:
        return "The requested format is not supported or available";
    default:
        return std::string("Unknown error code: ") + std::to_string(code);
    }
}

static void glfwErrorCallback(int code, const char *description)
{
    std::cerr << "GLFW Error: { " << IntepretGLFWerrorcode(code) << " } : " << description << std::endl;
}

vui::Graphics::Graphics()
{
    bool success = glfwInit();
    assert(success);
    glfwSetErrorCallback(glfwErrorCallback);
}

vui::Graphics::~Graphics()
{
    glfwTerminate();
}
