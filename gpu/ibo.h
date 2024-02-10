#pragma once

#include <GL/glew.h>

namespace eng
{
class IBO;
};

// virtual buffer object class
class eng::IBO
{
public:
    IBO();
    ~IBO();

    void bind() const;
    void unbind() const;
    void bufferData(const GLfloat* indices, GLsizeiptr size, GLenum usage = GL_STATIC_DRAW) const;

    template <typename T>
    void bufferData(const T* vertices, GLsizeiptr size, GLenum usage = GL_STATIC_DRAW)
    {
        glBufferData(GL_ARRAY_BUFFER, size, vertices, usage);
    }

private:
    GLuint m_id;
};
