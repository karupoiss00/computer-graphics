#include <sstream>
#include <fstream>
#include "Shader.h"
#include "ShaderLoader.h"

GLuint ShaderLoader::LoadShaderFromString(
    GLenum shaderType,
    std::string const& source,
    GLuint shaderId)
{
    Shader shader(shaderId);
    if (!shader)
    {
        shader.Create(shaderType);
    }
    shader.SetSource(source.c_str());

    return shader.Detach();
}

GLuint ShaderLoader::LoadShader(
    GLenum shaderType,
    std::istream& stream,
    GLuint shaderId)
{
    std::stringstream strStream;
    strStream << stream.rdbuf();

    return LoadShaderFromString(shaderType, strStream.str(), shaderId);
}

GLuint ShaderLoader::LoadShader(
    GLenum shaderType,
    const char* fileName,
    GLuint shaderId)
{
    std::ifstream stream(fileName);
    if (!stream.is_open())
    {
        throw std::runtime_error("Can't open shader file");
    }
    return LoadShader(shaderType, stream, shaderId);
}

GLuint ShaderLoader::LoadShader(
    GLenum shaderType,
    const wchar_t* fileName,
    GLuint shaderId)
{
    std::ifstream stream(fileName);
    if (!stream.is_open())
    {
        throw std::runtime_error("Can't open shader file");
    }
    return LoadShader(shaderType, stream, shaderId);
}