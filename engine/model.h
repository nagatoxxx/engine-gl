#pragma once

#include <glm/glm.hpp>

#include "../gpu/mesh.h"
#include "../gpu/shader.h"

namespace eng
{
class Model;
}

class eng::Model
{
public:
    Model(const std::string& objfile);
    ~Model();

    const glm::mat4& getModelMatrix() const;

    void render();
    void translate(const glm::vec3& translation);
    void rotate(float angle, const glm::vec3& axis);
    void scale(const glm::vec3& scale);

private:
    Mesh m_mesh;

    glm::mat4 m_modelMatrix;
};
