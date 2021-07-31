#include "mouse.h"

bool vui::Mouse::IsMouseButtonJustPressed(MouseButtonCode key) const
{
    return m_ButtonStateCurrent[key] && !m_ButtonStatePrevious[key];
}

bool vui::Mouse::IsMouseButtonJustReleased(MouseButtonCode key) const
{
    return m_ButtonStatePrevious[key] && !m_ButtonStateCurrent[key];
}

bool vui::Mouse::IsMouseButtonHeldDown(MouseButtonCode key) const
{
    return m_ButtonStatePrevious[key] && m_ButtonStateCurrent[key];
}

std::pair<int, int> vui::Mouse::GetPos() const
{
    return {x, y};
}

int vui::Mouse::GetPosX() const
{
    return x;
}

int vui::Mouse::GetPosY() const
{
    return y;
}
