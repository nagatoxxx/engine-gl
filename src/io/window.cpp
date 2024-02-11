#include <stdexcept>

#include "../../include/io/window.h"
#include "../../include/utility/logger.h"

using namespace eng;

Window::Window(int width, int height, const std::string& title) : m_width(width), m_height(height), m_title(title)
{
    init();

    Logger::log("Window created");
}

Window::~Window()
{
    glfwDestroyWindow(m_window);
    glfwTerminate();

    Logger::log("Window destroyed");
}

void Window::init()
{
    if (!glfwInit()) {
        throw std::runtime_error("Failed to init GLFW");
    }

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);

    if (m_window == nullptr) {
        throw std::runtime_error("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(m_window);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        throw std::runtime_error("Failed to init GLEW");
    }
    glViewport(0, 0, m_width, m_height);

    // input setup
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetKeyCallback(m_window, &Window::keyCallback);
    glfwSetCursorPosCallback(m_window, &Window::cursorPositionCallback);
    glfwSetCursorPos(m_window, m_width / 2.0f, m_height / 2.0f);
}

/* static */ void Window::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    EventSystem::sendEvent<KeyboardEvent>(KeyboardEvent(key, action));
}

/* static */ void Window::cursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
    EventSystem::sendEvent<MouseEvent>(MouseEvent(xpos, ypos));
}


bool Window::shouldClose() const
{
    return glfwWindowShouldClose(m_window);
}

float Window::getAspectRatio() const
{
    return static_cast<float>(m_width) / m_height;
}

void Window::setKeyboardPtr(std::shared_ptr<Keyboard> keyboard)
{
    if (keyboard == nullptr) {
        return;
    }
    m_keyboard = keyboard;

    EventSystem::registerEventCallback(eng::EventType::KeyPressed,
                                       [this](std::shared_ptr<Event> e)
                                       {
                                           std::shared_ptr<KeyboardEvent> ke = std::dynamic_pointer_cast<KeyboardEvent>(e);
                                           this->m_keyboard->setKeyState(ke->key(), ke->action());
                                       });

    Logger::log("Window: Keyboard pointer set");
}

void Window::setMousePtr(std::shared_ptr<Mouse> mouse)
{
    if (mouse == nullptr) {
        return;
    }
    m_mouse = mouse;

    EventSystem::registerEventCallback(eng::EventType::MouseMoved,
                                       [this](std::shared_ptr<Event> e)
                                       {
                                           std::shared_ptr<MouseEvent> me = std::dynamic_pointer_cast<MouseEvent>(e);
                                           this->m_mouse->setPosition(me->x(), me->y());
                                       });

    Logger::log("Window: Mouse pointer set");
}

void Window::pollEvents()
{
    glfwPollEvents();
}

void Window::swapBuffers()
{
    glfwSwapBuffers(m_window);
}
