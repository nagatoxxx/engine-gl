#pragma once

#include <iostream>
#include <string>

namespace eng
{
class Logger;
}

class eng::Logger
{
public:
    static void log(const std::string& msg);

private:
};
