#include "vbo.h"

using namespace eng;

VBO::VBO()
{
    glGenBuffers(1, &m_id);
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
    glBufferData(GL_ARRAY_BUFFER, size, vertices, usage);
}
