#pragma once

#include <memory>
#include <string>

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include "../engine/eventsystem.h"
#include "keyboard.h"
#include "mouse.h"

namespace eng
{
class Window;
} // namespace eng

class eng::Window
{
public:
    Window(int width, int height, const std::string& title);
    virtual ~Window();

    bool  shouldClose() const;
    float getAspectRatio() const;

    void setKeyboardPtr(std::shared_ptr<Keyboard> keyboard);
    void setMousePtr(std::shared_ptr<Mouse> mouse);

    void pollEvents();
    void swapBuffers();

private:
    void init();

    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
    static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);

private:
    int         m_width;
    int         m_height;
    std::string m_title;

    GLFWwindow* m_window;
    // std::unique_ptr<GLFWwindow>    m_window{nullptr};
    std::shared_ptr<eng::Keyboard> m_keyboard{nullptr};
    std::shared_ptr<eng::Mouse>    m_mouse{nullptr};
};
