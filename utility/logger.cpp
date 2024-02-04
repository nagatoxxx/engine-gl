#include <iostream>

#include "logger.h"
#include "timer.h"

using namespace eng;

static Timer timer;

/* static */ void Logger::log(const std::string& msg)
{
    uint64_t seconds = timer.getElapsedTime();
    std::cout << "[LOG] " << msg << " [" << seconds << " ms]" << '\n';
}
