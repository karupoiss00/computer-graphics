#pragma once
#include <string>
#include <cassert>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Program.h"

class ProgramInfo
{
public:
    ProgramInfo(GLuint program);

     static std::string TypeToString(GLenum type);

    GLuint GetActiveUniforms()const;

    void PrintUniformInfo(GLuint index, std::ostream& stream)const;
    void Print(std::ostream& stream) const;

private:
    ProgramInfo(ProgramInfo const&) = delete;
    ProgramInfo& operator=(ProgramInfo const&) = delete;

    ProgramHandle m_program;
};