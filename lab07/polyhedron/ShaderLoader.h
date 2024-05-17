#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class ShaderLoader
{
public:
    GLuint LoadShader(
        GLenum shaderType,
        const wchar_t* fileName,
        GLuint shaderId = 0);
    GLuint LoadShader(
        GLenum shaderType,
        const char* fileName,
        GLuint shaderId = 0);

    GLuint LoadShader(
        GLenum shaderType,
        std::istream& stream,
        GLuint shaderId = 0);
    GLuint LoadShaderFromString(
        GLenum shaderType,
        std::string const& source,
        GLuint shaderId = 0
    );
};