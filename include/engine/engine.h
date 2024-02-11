#pragma once

#include <memory>

#include "../io/keyboard.h"
#include "../io/mouse.h"
#include "../io/window.h"
#include "../utility/logger.h"
#include "../utility/timer.h"
#include "camera.h"
#include "object.h"
#include "world.h"

namespace eng
{
class Engine;
}

class eng::Engine
{
public:
    Engine(int windowWidth, int windowHeight, const std::string& windowTitle);
    virtual ~Engine();

    void run();

private:
    virtual void update() = 0;

protected:
    std::unique_ptr<eng::Window>   m_window;
    std::shared_ptr<eng::Keyboard> m_keyboard;
    std::shared_ptr<eng::Mouse>    m_mouse;
    std::unique_ptr<eng::Timer>    m_timer;

    World m_world;
};
