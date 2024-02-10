#pragma once

#include <glm/glm.hpp>

namespace eng
{
class Camera;
}

class eng::Camera
{
public:
    Camera(const glm::vec3& position, const glm::vec3& front, const glm::vec3& up);
    ~Camera();

    glm::vec3& position();
    glm::vec3& front();
    glm::vec3& up();
    glm::vec3  right() const;

    glm::mat4 getViewMatrix();
    float     getFov() const;

    void incAngles(float yaw, float pitch);
    void setSensivity(float sensivity);
    void setFov(float fov);

private:
    void update();

private:
    glm::vec3       m_position;
    glm::vec3       m_front;
    glm::vec3       m_up;
    glm::vec3       m_right;
    const glm::vec3 m_globalUp;

    float m_pitchAngle;
    float m_yawAngle;

    float m_sensivity;
    float m_fov;

    bool m_isUpdated;
};
