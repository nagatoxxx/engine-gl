#include "../../include/gpu/vbo.h"

using namespace eng;

VBO::VBO()
{
    glGenBuffers(1, &m_id);
}

VBO::VBO(const VBO& other)
{
}

VBO::~VBO()
{
    this->unbind();
    glDeleteBuffers(1, &m_id);
}

void VBO::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

void VBO::unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::bufferData(const GLfloat* vertices, GLsizeiptr size, GLenum usage /* = GL_STATIC_DRAW */) const
{
    this->bind();
    glBufferData(GL_ARRAY_BUFFER, size, vertices, usage);
}
