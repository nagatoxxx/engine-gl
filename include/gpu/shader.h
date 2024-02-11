#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <GL/glew.h>

namespace eng
{
class Shader;
}

class eng::Shader
{
public:
    Shader(const std::string& vertexPath, const std::string& fragmentPath);

    void use() const;

    GLuint getProgram() const
    {
        return m_program;
    };

private:
    GLuint m_program;
};
