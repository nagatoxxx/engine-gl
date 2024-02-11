#pragma once

#include <GL/glew.h>

namespace eng
{
class VAO;
}

// vertex array object class
class eng::VAO
{
public:
    VAO();
    ~VAO();

    void bind() const;
    void unbind() const;
    void attribPointer(GLuint location, GLint size, GLenum type, GLsizei stride, const void* pointer, GLboolean normalized = false) const;

private:
    GLuint m_id;
};
