#include <glm/gtc/matrix_transform.hpp>
#include <glm/trigonometric.hpp>

#include "../utility/logger.h"
#include "camera.h"

using namespace eng;

Camera::Camera(const glm::vec3& position, const glm::vec3& front, const glm::vec3& up)
: m_position(position),
  m_front(front),
  m_up(up),
  m_right(glm::cross(front, up)),
  m_globalUp(glm::vec3(0.0f, 1.0f, 0.0f)),
  m_pitchAngle(0.0f),
  m_yawAngle(-90.0f),
  m_sensivity(0.18f),
  m_fov(45.0f),
  m_isUpdated(true)
{
    Logger::log("Camera created");
}

Camera::~Camera()
{
    Logger::log("Camera destroyed");
}

glm::vec3& Camera::position()
{
    return m_position;
}

glm::vec3& Camera::front()
{
    return m_front;
}

glm::vec3& Camera::up()
{
    return m_up;
}

glm::vec3 Camera::right() const
{
    return m_right;
}

glm::mat4 Camera::getViewMatrix()
{
    if (!m_isUpdated)
        this->update();
    return glm::lookAt(m_position, m_position + m_front, m_up);
}

float Camera::getFov() const
{
    return m_fov;
}

void Camera::incAngles(float yaw, float pitch)
{
    m_pitchAngle += pitch * m_sensivity;
    m_yawAngle += yaw * m_sensivity;
    if (m_pitchAngle > 89.0f)
        m_pitchAngle = 89.0f;
    if (m_pitchAngle < -89.0f)
        m_pitchAngle = -89.0f;

    m_isUpdated = false;
}

void Camera::setSensivity(float sensivity)
{
    m_sensivity = sensivity;
}

void Camera::setFov(float fov)
{
    m_fov = fov;
}

void Camera::update()
{
    glm::vec3 front;
    front.x = glm::cos(glm::radians(m_yawAngle)) * glm::cos(glm::radians(m_pitchAngle));
    front.y = glm::sin(glm::radians(m_pitchAngle));
    front.z = glm::sin(glm::radians(m_yawAngle)) * glm::cos(glm::radians(m_pitchAngle));
    m_front = glm::normalize(front);

    m_right = glm::normalize(glm::cross(m_front, m_globalUp));
    m_up    = glm::normalize(glm::cross(m_right, m_front));
}
