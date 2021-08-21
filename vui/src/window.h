#pragma once

#include "mouse.h"
#include "keyboard.h"

#include <GLFW/glfw3.h>

namespace vui
{
    class Window
    {
    public:
        Window(const char *title, int32_t width, int32_t height);
        ~Window();

        Window(const Window &other);
        Window(Window &&other) noexcept;

        Window &operator=(const Window &other) = delete;
        Window &operator=(Window &&other) noexcept = delete;

        bool ProcessInput();
        void SwapBuffers();

        GLFWwindow *GetWindowHandle() const { return m_WindowHandle; }

    private:
        void CreateWindowInternal();

    public:
        Keyboard m_Keyboard;
        Mouse m_Mouse;

        std::pair<int32_t, int32_t> m_WindowSize;
        std::pair<int32_t, int32_t> m_FramebufferSize;

    private:
        GLFWwindow *m_WindowHandle;
        const char *m_Title;
    };
}