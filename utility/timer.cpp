#include "timer.h"
#include "logger.h"

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
    m_startTime = m_clock.now();

    Logger::log("Timer started");
}

float Timer::reset()
{
    m_endTime = m_clock.now();

    std::chrono::duration<float> elapsedTime = m_endTime - m_startTime;

    m_startTime = m_clock.now();

    return elapsedTime.count();
}

uint64_t Timer::getElapsedTime()
{
    m_endTime = m_clock.now();

    std::chrono::duration elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(m_endTime - m_startTime);

    return elapsedTime.count();
}
