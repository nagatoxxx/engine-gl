#include <iostream>

#include "../../include/utility/logger.h"
#include "../../include/utility/timer.h"

using namespace eng;

static Timer timer;

/* static */ void Logger::log(const std::string& msg)
{
    uint64_t time = timer.timeSinceStart();
    std::cout << "[LOG] " << msg << " [" << time << " ms]" << '\n';
}
