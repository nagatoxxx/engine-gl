#include "world.h"
#include "../utility/logger.h"

using namespace eng;

World::World()
{
    Logger::log("World created");
}

/* virtual */ World::~World()
{
    Logger::log("World destroyed");
}
