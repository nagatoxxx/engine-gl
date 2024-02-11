#include "../../include/utility/timer.h"
#include "../../include/utility/logger.h"

using namespace eng;

Timer::Timer(bool start /* = false */)
{
    if (start) {
        this->start();
    }

    Logger::log("Timer created");
}

Timer::~Timer()
{
    Logger::log("Timer destroyed");
}

void Timer::start()
{
    m_startTime      = m_clock.now();
    m_constStartTime = m_startTime;

    Logger::log("Timer started");
}

float Timer::reset()
{
    m_endTime = m_clock.now();

    std::chrono::duration<float> elapsedTime = m_endTime - m_startTime;

    m_startTime = m_clock.now();

    return elapsedTime.count();
}

float Timer::timeSinceStart()
{
    m_endTime = m_clock.now();

    std::chrono::duration<float> elapsedTime = m_endTime - m_constStartTime;

    return elapsedTime.count();
}
