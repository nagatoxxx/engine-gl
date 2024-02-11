#pragma once

#include <chrono>

namespace eng
{
class Timer;
}

class eng::Timer
{
public:
    Timer(bool start = false);
    ~Timer();

    void start();

    float reset(); // returns elapsed time in seconds and resets timer
    float timeSinceStart();

private:
    std::chrono::high_resolution_clock             m_clock;
    std::chrono::high_resolution_clock::time_point m_startTime;
    std::chrono::high_resolution_clock::time_point m_endTime;

    std::chrono::high_resolution_clock::time_point m_constStartTime;
};
