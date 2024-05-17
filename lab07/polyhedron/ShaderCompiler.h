#pragma once
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class ShaderCompiler
{
public:
    ShaderCompiler() = default;

    void CompileShader(GLuint shader);
    void CheckStatus();
private:
    ShaderCompiler(ShaderCompiler const&) = delete;
    ShaderCompiler& operator=(ShaderCompiler const&) = delete;
    std::vector<GLuint> m_shaders;
};