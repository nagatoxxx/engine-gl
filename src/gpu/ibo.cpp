#include "../../include/gpu/ibo.h"

using namespace eng;

IBO::IBO()
{
    glGenBuffers(1, &m_id);
}

IBO::~IBO()
{
    this->unbind();
    glDeleteBuffers(1, &m_id);
}

void IBO::bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
}

void IBO::unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IBO::bufferData(const GLfloat* indices, GLsizeiptr size, GLenum usage /* = GL_STATIC_DRAW */) const
{
    this->bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, usage);
}
