#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "ibo.h"
#include "texture.h"
#include "vao.h"
#include "vbo.h"

namespace eng
{
class Mesh;
}

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
};

class eng::Mesh
{
public:
    Mesh();
    Mesh(const std::string& filepath);
    ~Mesh();

    void setDrawMode(GLenum drawMode, GLenum primitiveType = GL_TRIANGLES);
    void loadFromFile(const std::string& filepath);

    void draw();

private:
    virtual void initAttribPointer();
    void         calculateNormals();

private:
    std::vector<Vertex> m_vertices;
    std::vector<GLuint> m_indices;

    VBO m_vbo;
    VAO m_vao;

    GLenum m_drawMode, m_primitiveType;
};
