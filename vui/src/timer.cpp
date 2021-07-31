#include "timer.h"

vui::Timer::Timer()
    : m_Start(TimePoint::clock::now())
{
}

void vui::Timer::Renew() { m_Start = TimePoint::clock::now(); }

float vui::Timer::GetElapsedMilli() const
{
    using Milli = std::chrono::duration<float, std::milli>;

    return std::chrono::duration_cast<Milli>((TimePoint::clock::now() - m_Start))
        .count();
}

float vui::Timer::GetElapsedSeconds() const { return GetElapsedMilli() / 1000.0f; }