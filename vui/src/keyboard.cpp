#include "keyboard.h"

bool vui::Keyboard::IsKeyJustPressed(KeyCode key)
{
    return m_KeyStateCurrent[key] && !m_KeyStatePrevious[key];
}

bool vui::Keyboard::IsKeyJustReleased(KeyCode key)
{
    return m_KeyStatePrevious[key] && !m_KeyStateCurrent[key];
}

bool vui::Keyboard::IsKeyHeldDown(KeyCode key)
{
    return m_KeyStatePrevious[key] && m_KeyStateCurrent[key];
}
