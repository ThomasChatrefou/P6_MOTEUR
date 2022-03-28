#pragma once

#include <chrono>


using Clock = std::chrono::high_resolution_clock;
using Timestamp = Clock::time_point;
using Duration = Clock::duration;


inline float Seconds(Duration const& iDuration)
{
    return std::chrono::duration_cast<std::chrono::duration<float>>(iDuration).count();
}


class Time
{
public:
    Time();

    float getTime() { return Seconds(m_Clock.now() - m_Start); }
    float getDeltaTime() { return m_DeltaTime; }

private:
    Clock m_Clock;
    Timestamp m_Start;
    Timestamp m_LastFrame;
    float m_DeltaTime;

public:
    void Update();
};