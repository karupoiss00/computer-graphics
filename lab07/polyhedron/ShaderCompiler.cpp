#include <sstream>
#include "Shader.h"
#include "ShaderCompiler.h"

void ShaderCompiler::CompileShader(GLuint shader)
{
    ShaderHandle sh(shader);
    sh.Compile();
    m_shaders.push_back(shader);
}

void ShaderCompiler::CheckStatus()
{
    std::stringstream strm;

    bool hasErrors = false;

    for (size_t i = 0; i < m_shaders.size(); ++i)
    {
        ShaderHandle shader(m_shaders[i]);
        if (shader.GetParameter(GL_COMPILE_STATUS) != GL_TRUE)
        {
            hasErrors = true;
            strm << "Shader " << shader << " compilation failed: " <<
                shader.GetInfoLog() << "\n";
        }
    }

    m_shaders.clear();

    if (hasErrors)
    {
        throw std::runtime_error(strm.str());
    }
}