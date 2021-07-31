#pragma once

#include <bitset>

namespace vui
{
    enum MouseButtonCode
    {
        UnknownButton,

        LeftMouseButton,
        MiddleMouseButton,
        RightMouseButton,

        MouseButton4,
        MouseButton5,
        MouseButton6,
        MouseButton7,
        MouseButton8,

        NumSupportedButtons
    };

    class Mouse
    {
    public:
        bool IsMouseButtonJustPressed(MouseButtonCode key) const;
        bool IsMouseButtonJustReleased(MouseButtonCode key) const;
        bool IsMouseButtonHeldDown(MouseButtonCode key) const;
        std::pair<int, int> GetPos() const;
        int GetPosX() const;
        int GetPosY() const;

    public:
        int x = 0;
        int y = 0;

        std::bitset<MouseButtonCode::NumSupportedButtons> m_ButtonStateCurrent;
        std::bitset<MouseButtonCode::NumSupportedButtons> m_ButtonStatePrevious;
    };
} // namespace vui
