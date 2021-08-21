#include "window.h"

static vui::KeyCode GetKeyCodeFromGLFWKey(int key)
{
    switch (key)
    {
    case GLFW_KEY_UNKNOWN:
        return vui::KeyCode::UnknownKey;
    case GLFW_KEY_BACKSPACE:
        return vui::KeyCode::Backspace;
    case GLFW_KEY_TAB:
        return vui::KeyCode::Tab;
    case GLFW_KEY_ENTER:
        return vui::KeyCode::Return;
    case GLFW_KEY_PAUSE:
        return vui::KeyCode::Pause;
    case GLFW_KEY_ESCAPE:
        return vui::KeyCode::Escape;
    case GLFW_KEY_SPACE:
        return vui::KeyCode::Space;
    case GLFW_KEY_COMMA:
        return vui::KeyCode::Comma;
    case GLFW_KEY_MINUS:
        return vui::KeyCode::Minus;
    case GLFW_KEY_PERIOD:
        return vui::KeyCode::Period;
    case GLFW_KEY_SLASH:
        return vui::KeyCode::Slash;
    case GLFW_KEY_0:
        return vui::KeyCode::Zero;
    case GLFW_KEY_1:
        return vui::KeyCode::One;
    case GLFW_KEY_2:
        return vui::KeyCode::Two;
    case GLFW_KEY_3:
        return vui::KeyCode::Three;
    case GLFW_KEY_4:
        return vui::KeyCode::Four;
    case GLFW_KEY_5:
        return vui::KeyCode::Five;
    case GLFW_KEY_6:
        return vui::KeyCode::Six;
    case GLFW_KEY_7:
        return vui::KeyCode::Seven;
    case GLFW_KEY_8:
        return vui::KeyCode::Eight;
    case GLFW_KEY_9:
        return vui::KeyCode::Nine;
    case GLFW_KEY_SEMICOLON:
        return vui::KeyCode::Semicolon;
    case GLFW_KEY_EQUAL:
        return vui::KeyCode::Equals;
    case GLFW_KEY_LEFT_BRACKET:
        return vui::KeyCode::LeftBracket;
    case GLFW_KEY_BACKSLASH:
        return vui::KeyCode::Backslash;
    case GLFW_KEY_RIGHT_BRACKET:
        return vui::KeyCode::RightBracket;
    case GLFW_KEY_A:
        return vui::KeyCode::A;
    case GLFW_KEY_B:
        return vui::KeyCode::B;
    case GLFW_KEY_C:
        return vui::KeyCode::C;
    case GLFW_KEY_D:
        return vui::KeyCode::D;
    case GLFW_KEY_E:
        return vui::KeyCode::E;
    case GLFW_KEY_F:
        return vui::KeyCode::F;
    case GLFW_KEY_G:
        return vui::KeyCode::G;
    case GLFW_KEY_H:
        return vui::KeyCode::H;
    case GLFW_KEY_I:
        return vui::KeyCode::I;
    case GLFW_KEY_J:
        return vui::KeyCode::J;
    case GLFW_KEY_K:
        return vui::KeyCode::K;
    case GLFW_KEY_L:
        return vui::KeyCode::L;
    case GLFW_KEY_M:
        return vui::KeyCode::M;
    case GLFW_KEY_N:
        return vui::KeyCode::N;
    case GLFW_KEY_O:
        return vui::KeyCode::O;
    case GLFW_KEY_P:
        return vui::KeyCode::P;
    case GLFW_KEY_Q:
        return vui::KeyCode::Q;
    case GLFW_KEY_R:
        return vui::KeyCode::R;
    case GLFW_KEY_S:
        return vui::KeyCode::S;
    case GLFW_KEY_T:
        return vui::KeyCode::T;
    case GLFW_KEY_U:
        return vui::KeyCode::U;
    case GLFW_KEY_V:
        return vui::KeyCode::V;
    case GLFW_KEY_W:
        return vui::KeyCode::W;
    case GLFW_KEY_X:
        return vui::KeyCode::X;
    case GLFW_KEY_Y:
        return vui::KeyCode::Y;
    case GLFW_KEY_Z:
        return vui::KeyCode::Z;
    case GLFW_KEY_DELETE:
        return vui::KeyCode::Delete;
    case GLFW_KEY_KP_DECIMAL:
        return vui::KeyCode::Decimal;
    case GLFW_KEY_KP_DIVIDE:
        return vui::KeyCode::Divide;
    case GLFW_KEY_KP_MULTIPLY:
        return vui::KeyCode::Multiply;
    case GLFW_KEY_KP_SUBTRACT:
        return vui::KeyCode::Subtract;
    case GLFW_KEY_KP_ADD:
        return vui::KeyCode::Add;
    case GLFW_KEY_KP_ENTER:
        return vui::KeyCode::NumpadEnter;
    case GLFW_KEY_KP_EQUAL:
        return vui::KeyCode::NumpadEquals;
    case GLFW_KEY_UP:
        return vui::KeyCode::ArrowUp;
    case GLFW_KEY_DOWN:
        return vui::KeyCode::ArrowDown;
    case GLFW_KEY_RIGHT:
        return vui::KeyCode::ArrowRight;
    case GLFW_KEY_LEFT:
        return vui::KeyCode::ArrowLeft;
    case GLFW_KEY_INSERT:
        return vui::KeyCode::Insert;
    case GLFW_KEY_HOME:
        return vui::KeyCode::Home;
    case GLFW_KEY_END:
        return vui::KeyCode::End;
    case GLFW_KEY_PAGE_UP:
        return vui::KeyCode::PageUp;
    case GLFW_KEY_PAGE_DOWN:
        return vui::KeyCode::PageDown;
    case GLFW_KEY_F1:
        return vui::KeyCode::F1;
    case GLFW_KEY_F2:
        return vui::KeyCode::F2;
    case GLFW_KEY_F3:
        return vui::KeyCode::F3;
    case GLFW_KEY_F4:
        return vui::KeyCode::F4;
    case GLFW_KEY_F5:
        return vui::KeyCode::F5;
    case GLFW_KEY_F6:
        return vui::KeyCode::F6;
    case GLFW_KEY_F7:
        return vui::KeyCode::F7;
    case GLFW_KEY_F8:
        return vui::KeyCode::F8;
    case GLFW_KEY_F9:
        return vui::KeyCode::F9;
    case GLFW_KEY_F10:
        return vui::KeyCode::F10;
    case GLFW_KEY_F11:
        return vui::KeyCode::F11;
    case GLFW_KEY_F12:
        return vui::KeyCode::F12;
    case GLFW_KEY_F13:
        return vui::KeyCode::F13;
    case GLFW_KEY_F14:
        return vui::KeyCode::F14;
    case GLFW_KEY_F15:
        return vui::KeyCode::F15;
    case GLFW_KEY_RIGHT_SHIFT:
        return vui::KeyCode::RightShift;
    case GLFW_KEY_LEFT_SHIFT:
        return vui::KeyCode::LeftShift;
    case GLFW_KEY_RIGHT_CONTROL:
        return vui::KeyCode::RightControl;
    case GLFW_KEY_LEFT_CONTROL:
        return vui::KeyCode::LeftControl;
    case GLFW_KEY_RIGHT_ALT:
        return vui::KeyCode::RightAlt;
    case GLFW_KEY_LEFT_ALT:
        return vui::KeyCode::LeftAlt;
    case GLFW_KEY_MENU:
        return vui::KeyCode::AppMenu;
    case GLFW_KEY_PRINT_SCREEN:
        return vui::KeyCode::SysRq;
    }
    return vui::KeyCode::UnknownKey;
}

static vui::MouseButtonCode GetMouseButtonCodeFromGLFWButton(int button)
{
    switch (button)
    {
    case GLFW_MOUSE_BUTTON_LEFT:
        return vui::MouseButtonCode::LeftMouseButton;
    case GLFW_MOUSE_BUTTON_MIDDLE:
        return vui::MouseButtonCode::MiddleMouseButton;
    case GLFW_MOUSE_BUTTON_RIGHT:
        return vui::MouseButtonCode::RightMouseButton;
    case GLFW_MOUSE_BUTTON_4:
        return vui::MouseButtonCode::MouseButton4;
    case GLFW_MOUSE_BUTTON_5:
        return vui::MouseButtonCode::MouseButton5;
    case GLFW_MOUSE_BUTTON_6:
        return vui::MouseButtonCode::MouseButton6;
    case GLFW_MOUSE_BUTTON_7:
        return vui::MouseButtonCode::MouseButton7;
    case GLFW_MOUSE_BUTTON_8:
        return vui::MouseButtonCode::MouseButton8;
    }

    return vui::MouseButtonCode::UnknownButton;
}

static void OnKeyEventCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    vui::Window *userWindow = static_cast<vui::Window *>(glfwGetWindowUserPointer(window));
    switch (action)
    {
    case GLFW_PRESS:
    {
        userWindow->m_Keyboard.m_KeyStateCurrent[GetKeyCodeFromGLFWKey(key)] = true;
        break;
    }
    case GLFW_RELEASE:
    {
        userWindow->m_Keyboard.m_KeyStateCurrent[GetKeyCodeFromGLFWKey(key)] = false;
        break;
    }
    }
}

static void OnMouseEventCallback(GLFWwindow *window, int button, int action, int mods)
{
    vui::Window *userWindow = static_cast<vui::Window *>(glfwGetWindowUserPointer(window));
    switch (action)
    {
    case GLFW_PRESS:
    {
        userWindow->m_Mouse.m_ButtonStateCurrent[GetMouseButtonCodeFromGLFWButton(button)] = true;
        break;
    }
    case GLFW_RELEASE:
    {
        userWindow->m_Mouse.m_ButtonStateCurrent[GetMouseButtonCodeFromGLFWButton(button)] = false;
        break;
    }
    }
}

static void OnMouseMoveEventCallback(GLFWwindow *window, double xPos, double yPos)
{
    vui::Window *userWindow = static_cast<vui::Window *>(glfwGetWindowUserPointer(window));
    userWindow->m_Mouse.x = xPos;
    userWindow->m_Mouse.y = yPos;
}

static void OnFramebufferResizedCallback(GLFWwindow *window, int width, int height)
{
    vui::Window *userWindow = static_cast<vui::Window *>(glfwGetWindowUserPointer(window));
    userWindow->m_FramebufferSize = {width, height};
}

static void OnWindowResizedCallback(GLFWwindow *window, int width, int height)
{
    vui::Window *userWindow = static_cast<vui::Window *>(glfwGetWindowUserPointer(window));
    userWindow->m_WindowSize = {width, height};
}

vui::Window::Window(const char *title, int32_t width, int32_t height)
    : m_Keyboard(),
      m_Mouse(),
      m_WindowSize(width, height),
      m_FramebufferSize(0, 0),
      m_WindowHandle(nullptr),
      m_Title(title)
{
    CreateWindowInternal();
}

vui::Window::~Window()
{
    if (m_WindowHandle)
    {
        glfwDestroyWindow(m_WindowHandle);
    }
}

vui::Window::Window(const Window &other)
    : m_Keyboard(other.m_Keyboard),
      m_Mouse(other.m_Mouse),
      m_WindowSize(other.m_WindowSize),
      m_FramebufferSize(other.m_FramebufferSize),
      m_WindowHandle(nullptr),
      m_Title(other.m_Title)
{
    CreateWindowInternal();
}

vui::Window::Window(Window &&other) noexcept
    : m_Keyboard(std::move(other.m_Keyboard)),
      m_Mouse(std::move(other.m_Mouse)),
      m_WindowSize(std::move(other.m_WindowSize)),
      m_FramebufferSize(std::move(other.m_FramebufferSize)),
      m_WindowHandle(other.m_WindowHandle),
      m_Title(other.m_Title)
{
    other.m_WindowHandle = nullptr;
    glfwSetWindowUserPointer(m_WindowHandle, this);
}

bool vui::Window::ProcessInput()
{
    m_Keyboard.m_KeyStatePrevious = m_Keyboard.m_KeyStateCurrent;
    m_Mouse.m_ButtonStatePrevious = m_Mouse.m_ButtonStateCurrent;

    glfwPollEvents();
    return glfwWindowShouldClose(m_WindowHandle);
}

void vui::Window::SwapBuffers()
{
    glfwSwapBuffers(m_WindowHandle);
}

void vui::Window::CreateWindowInternal()
{
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    auto [width, height] = m_WindowSize;
    m_WindowHandle = glfwCreateWindow(width, height, m_Title, nullptr, nullptr);

    glfwSetWindowUserPointer(m_WindowHandle, this);
    glfwSetKeyCallback(m_WindowHandle, OnKeyEventCallback);
    glfwSetMouseButtonCallback(m_WindowHandle, OnMouseEventCallback);
    glfwSetCursorPosCallback(m_WindowHandle, OnMouseMoveEventCallback);
    glfwSetFramebufferSizeCallback(m_WindowHandle, OnFramebufferResizedCallback);
    glfwSetWindowSizeCallback(m_WindowHandle, OnWindowResizedCallback);

    auto &[framebufferWidth, framebufferHeight] = m_FramebufferSize;
    glfwGetFramebufferSize(m_WindowHandle, &framebufferWidth, &framebufferHeight);
}
