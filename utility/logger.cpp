#include <iostream>

#include "logger.h"
#include "timer.h"

using namespace eng;

static Timer timer;

/* static */ void Logger::log(const std::string& msg)
{
    uint64_t time = timer.timeSinceStart();
    std::cout << "[LOG] " << msg << " [" << time << " ms]" << '\n';
}
