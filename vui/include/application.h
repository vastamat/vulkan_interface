#pragma once

#include <memory>

namespace vui
{
    class Window;
    class Graphics;
    class VulkanRenderer;
   
    class Application
    {
    public:
        Application();
        void Run();

    private:
        bool Update();
        void Render();

    private:
        std::shared_ptr<Graphics> m_Graphics;
        std::shared_ptr<Window> m_MainWindow;
        std::shared_ptr<VulkanRenderer> m_Renderer;
    };
} // namespace vui
