#pragma once
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class ProgramLinker
{
public:
    void LinkProgram(GLuint program);
    void CheckStatus();
private:
    std::vector<GLuint> m_programs;
};