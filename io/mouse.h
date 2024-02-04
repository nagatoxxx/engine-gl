#pragma once

#include <glm/glm.hpp>

namespace eng
{
class Mouse;
}

class eng::Mouse
{
public:
    Mouse(double x, double y);
    ~Mouse();

    glm::vec2 getDelta();
    void      setPosition(double x, double y);

private:
    double m_lastX;
    double m_lastY;
    double m_currentX;
    double m_currentY;
};
