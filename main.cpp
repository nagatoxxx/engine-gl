#include <iostream>

#include "engine/engine.h"

int main(int argc, char* argv[])
{
    try {
        eng::Engine engine;
        engine.run();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}