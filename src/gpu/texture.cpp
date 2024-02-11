#include <stdexcept>

#include <soil2/SOIL2.h>

#include "../../include/gpu/texture.h"

using namespace eng;

Texture::Texture(const std::string& image, GLenum texType, GLenum format, GLenum pixelType) : m_type(texType)
{
    int width, height;

    // reading image to the bytes array
    unsigned char* bytes = SOIL_load_image(image.c_str(), &width, &height, 0, SOIL_LOAD_RGB);

    if (bytes == NULL) {
        throw std::runtime_error("Failed to load image");
    }

    glGenTextures(1, &m_id);
    glBindTexture(m_type, m_id);

    glTexParameteri(m_type, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(m_type, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(m_type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(m_type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(texType, 0, GL_RGB, width, height, 0, format, pixelType, bytes);
    glGenerateMipmap(texType);

    SOIL_free_image_data(bytes);
    this->unbind();
}

Texture::~Texture()
{
    this->unbind();
    glDeleteTextures(1, &m_id);
}

void Texture::bind() const
{
    glBindTexture(m_type, m_id);
}

void Texture::unbind() const
{
    glBindTexture(m_type, 0);
}

/* static */ void Texture::enableTexureUnit(GLuint i)
{
    glActiveTexture(GL_TEXTURE0 + i);
}

void Texture::setTextureUnit(GLuint shaderID, const std::string& uniform, GLuint unit) const
{
    // gets the location of the uniform
    GLint uniformLocation = glGetUniformLocation(shaderID, uniform.c_str());

    if (uniformLocation == -1) {
        throw std::runtime_error("Could not find uniform: " + uniform);
    }
    // sets the value of the uniform
    glUniform1i(uniformLocation, unit);
}
