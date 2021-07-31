#pragma once

#include <chrono>

using TimePoint = std::chrono::time_point<std::chrono::steady_clock>;

namespace vui
{
    class Timer
    {
    public:
        Timer();

        void Renew();

        float GetElapsedMilli() const;
        float GetElapsedSeconds() const;

    private:
        TimePoint m_Start;
    };
}