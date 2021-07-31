#pragma once

#include <bitset>

namespace vui
{
    enum KeyCode
    {
        UnknownKey,

        Backspace,
        Tab,
        Return,
        Pause,
        Escape,
        Space,
        Comma,
        Minus,
        Period,
        Slash,
        Zero,
        One,
        Two,
        Three,
        Four,
        Five,
        Six,
        Seven,
        Eight,
        Nine,
        Colon,
        Semicolon,
        Equals,
        LeftBracket,
        Backslash,
        RightBracket,
        A,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
        J,
        K,
        L,
        M,
        N,
        O,
        P,
        Q,
        R,
        S,
        T,
        U,
        V,
        W,
        X,
        Y,
        Z,
        Delete,
        Decimal,
        Divide,
        Multiply,
        Subtract,
        Add,
        NumpadEnter,
        NumpadEquals,
        ArrowUp,
        ArrowDown,
        ArrowRight,
        ArrowLeft,
        Insert,
        Home,
        End,
        PageUp,
        PageDown,
        F1,
        F2,
        F3,
        F4,
        F5,
        F6,
        F7,
        F8,
        F9,
        F10,
        F11,
        F12,
        F13,
        F14,
        F15,
        RightShift,
        LeftShift,
        RightControl,
        LeftControl,
        RightAlt,
        LeftAlt,
        SysRq,
        AppMenu,
        Power,

        NumSupportedKeys
    };

    class Keyboard
    {
    public:
        bool IsKeyJustPressed(KeyCode key);
        bool IsKeyJustReleased(KeyCode key);
        bool IsKeyHeldDown(KeyCode key);

    public:
        std::bitset<KeyCode::NumSupportedKeys> m_KeyStateCurrent;
        std::bitset<KeyCode::NumSupportedKeys> m_KeyStatePrevious;
    };
} // namespace vui
