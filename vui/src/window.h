#pragma once

#include "mouse.h"
#include "keyboard.h"

#include <GLFW/glfw3.h>

namespace vui
{
    class Window
    {
    public:
        Window(const char *title, int width, int height);
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

    private:
        GLFWwindow *m_WindowHandle;
        const char *m_Title;
        int m_Width;
        int m_Height;
    };
}