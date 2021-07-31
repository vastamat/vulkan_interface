#pragma once

#include <memory>

namespace vui
{
    class Window;
    class Graphics;

    class Application
    {
    public:
        Application();
        void Run();

    private:
        bool Update();

    private:
        std::shared_ptr<Graphics> m_Gfx;
        std::shared_ptr<Window> m_MainWindow;
    };
} // namespace vui
