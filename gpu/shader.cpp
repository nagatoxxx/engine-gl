#include "shader.h"

using namespace eng;

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
{
    std::string   vertexStr;
    std::string   fragmentStr;
    std::ifstream vertexFile;
    std::ifstream fragmentFile;

    vertexFile.exceptions(std::ifstream::badbit);
    fragmentFile.exceptions(std::ifstream::badbit);

    // reading shaders
    try {
        // reading vertex shader
        vertexFile.open(vertexPath);
        std::stringstream vertexStream;

        vertexStream << vertexFile.rdbuf();

        vertexFile.close();

        vertexStr = vertexStream.str();

        // reading fragment shader
        fragmentFile.open(fragmentPath);
        std::stringstream fragmentStream;

        fragmentStream << fragmentFile.rdbuf();

        fragmentFile.close();

        fragmentStr = fragmentStream.str();

    } catch (const std::exception& e) {
        throw e;
    }

    const GLchar* vertexCode   = vertexStr.c_str();
    const GLchar* fragmentCode = fragmentStr.c_str();

    // compiling shaders
    GLuint vertex, fragment;
    GLint  success;
    GLchar log[512];

    // vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexCode, NULL);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(vertex, 512, nullptr, log);
        throw std::runtime_error(log);
    }

    // fragment shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentCode, NULL);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(fragment, 512, nullptr, log);
        throw std::runtime_error(log);
    }

    m_program = glCreateProgram();
    glAttachShader(m_program, vertex);
    glAttachShader(m_program, fragment);
    glLinkProgram(m_program);

    glGetProgramiv(m_program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(m_program, 512, nullptr, log);
        throw std::runtime_error(log);
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use()
{
    glUseProgram(m_program);
}
