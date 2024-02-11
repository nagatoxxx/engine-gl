#include "../../include/io/mouse.h"

using namespace eng;

Mouse::Mouse(double x, double y) : m_lastX(x), m_lastY(y), m_currentX(x), m_currentY(y)
{
}

Mouse::~Mouse()
{
}

glm::vec2 Mouse::getDelta()
{
    glm::vec2 res(m_currentX - m_lastX, m_currentY - m_lastY);

    m_lastX = m_currentX;
    m_lastY = m_currentY;

    return res;
}

void Mouse::setPosition(double x, double y)
{
    m_lastX = m_currentX;
    m_lastY = m_currentY;

    m_currentX = x;
    m_currentY = y;
}
