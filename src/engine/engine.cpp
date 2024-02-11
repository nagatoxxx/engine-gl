#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../../include/engine/engine.h"

using namespace eng;

Engine::Engine(int windowWidth, int windowHeight, const std::string& windowTitle)
: m_window(std::make_unique<eng::Window>(windowWidth, windowHeight, windowTitle)),
  m_keyboard(std::make_shared<Keyboard>(Keyboard())),
  m_mouse(std::make_shared<Mouse>(Mouse(static_cast<double>(windowWidth) / 2, static_cast<double>(windowHeight) / 2))),
  m_timer(std::make_unique<Timer>(Timer())),
  m_world()
{
    glEnable(GL_DEPTH_TEST);

    m_window->setKeyboardPtr(m_keyboard);
    m_window->setMousePtr(m_mouse);

    Logger::log("Engine created");
}

/* virtual */ Engine::~Engine()
{
    Logger::log("Engine destroyed");
}

void Engine::run()
{
    m_timer->start();

    while (!m_window->shouldClose()) {
        m_window->pollEvents();
        EventSystem::pollEvents();

        this->update();

        m_window->swapBuffers();
    }
}
