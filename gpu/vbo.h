#pragma once

#include <GL/glew.h>

namespace eng
{
class VBO;
};

// virtual buffer object class
class eng::VBO
{
public:
    VBO();
    ~VBO();

    void bind() const;
    void unbind() const;
    void bufferData(const GLfloat* vertices, GLsizeiptr size, GLenum usage = GL_STATIC_DRAW) const;

    template <typename T>
    void bufferData(const T* vertices, GLsizeiptr size, GLenum usage = GL_STATIC_DRAW)
    {
        glBufferData(GL_ARRAY_BUFFER, size, vertices, usage);
    }

private:
    GLuint m_id;
};
