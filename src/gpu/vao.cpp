#include "../../include/gpu/vao.h"

using namespace eng;

VAO::VAO()
{
    glGenVertexArrays(1, &m_id);
}

VAO::~VAO()
{
    this->unbind();
    glDeleteVertexArrays(1, &m_id);
}

void VAO::bind() const
{
    glBindVertexArray(m_id);
}

void VAO::unbind() const
{
    glBindVertexArray(0);
}

void VAO::attribPointer(GLuint location, GLint size, GLenum type, GLsizei stride, const void* pointer, GLboolean normalized /* = false */) const
{
    glVertexAttribPointer(location, size, type, normalized, stride, pointer);
    glEnableVertexAttribArray(location);
}
