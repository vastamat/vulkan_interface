#include "application.h"

#include "graphics.h"
#include "window.h"
#include "timer.h"

#include <thread>

// Variable Render frame limiter (runs as quick as possible with a set limit)
// Must be more than the fixed update, or the sleep will disrupt the fixed timer
constexpr int c_MillisPerSecond = 1000;
constexpr float c_DesiredRenderFPS = 60.0f;
constexpr float c_DesiredRenderFrameMS = c_MillisPerSecond / c_DesiredRenderFPS;

void vui::Application::Run()
{
    Timer updateTimer;

    bool ShouldQuit = false;

    while (!ShouldQuit)
    {
        float delta = updateTimer.GetElapsedMilli();
        updateTimer.Renew();

        ShouldQuit = Update(/*delta*/);

        float elapsed = updateTimer.GetElapsedMilli();
        if (elapsed < c_DesiredRenderFrameMS)
        {
            std::this_thread::sleep_for(std::chrono::duration<float, std::milli>(
                c_DesiredRenderFrameMS - elapsed));
        }
    }
}

vui::Application::Application()
{
    m_Gfx = std::make_shared<Graphics>();
    m_MainWindow = std::make_shared<Window>("Vulkan Sandbox", 1280, 720);
}

bool vui::Application::Update()
{
    if (m_MainWindow->m_Keyboard.IsKeyJustPressed(vui::KeyCode::Tab))
    {
        printf("Pressed Tab \n");
    }
    if (m_MainWindow->m_Keyboard.IsKeyJustReleased(vui::KeyCode::Tab))
    {
        printf("Released Tab \n");
    }
    // if (m_MainWindow->m_Keyboard.IsKeyHeldDown(vui::KeyCode::Tab))
    // {
    //     printf("Holding down Tab \n");
    // }
    return m_MainWindow->ProcessInput();
}
