#pragma once

#include <memory>
#include <string>

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include "keyboard.h"
#include "mouse.h"

namespace eng
{
class Window;
} // namespace eng

struct Devices
{
    std::shared_ptr<eng::Keyboard> keyboard{nullptr};
    std::shared_ptr<eng::Mouse>    mouse{nullptr};
};

class eng::Window
{
public:
    Window(int width, int height, const std::string& title);
    virtual ~Window();

    bool shouldClose() const;

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
    Devices     m_devices;
};
