#pragma once

#include <string>

#include <GL/glew.h>

#include "shader.h"

namespace eng
{
class Texture;
}

class eng::Texture
{
public:
    Texture(const std::string& image, GLenum texType, GLenum format, GLenum pixelType);
    ~Texture();

    void bind() const;
    void unbind() const;

    void setTextureUnit(GLuint shaderID, const std::string& uniform, GLuint unit) const;

private:
    GLenum m_type;
    GLuint m_id;
};
