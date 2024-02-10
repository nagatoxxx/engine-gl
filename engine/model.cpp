#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "model.h"

using namespace eng;

Model::Model(const std::string& objfile) : m_mesh(objfile), m_modelMatrix(1.0f)
{
}

Model::~Model()
{
}

const glm::mat4& Model::getModelMatrix() const
{
    return m_modelMatrix;
}

void Model::render()
{
    // shader.use();

    m_mesh.draw();
}

void Model::translate(const glm::vec3& translation)
{
    m_modelMatrix = glm::translate(m_modelMatrix, translation);
}

void Model::rotate(float angle, const glm::vec3& axis)
{
    m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(angle), axis);
}

void Model::scale(const glm::vec3& scale)
{
    m_modelMatrix = glm::scale(m_modelMatrix, scale);
}
