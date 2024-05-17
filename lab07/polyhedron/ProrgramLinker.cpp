#include <sstream>
#include "Program.h"
#include "ProgramLinker.h"

void ProgramLinker::LinkProgram(GLuint program)
{
    ProgramHandle prog(program);
    prog.Link();
    m_programs.push_back(program);
}

void ProgramLinker::CheckStatus()
{
    std::stringstream strm;

    bool hasErrors = false;

    for (size_t i = 0; i < m_programs.size(); ++i)
    {
        ProgramHandle program(m_programs[i]);
        if (program.GetParameter(GL_LINK_STATUS) != GL_TRUE)
        {
            hasErrors = true;
            strm << "Program " << program << " linkage failed: " <<
                program.GetInfoLog() << "\n";
        }
    }

    m_programs.clear();

    if (hasErrors)
    {
        throw std::runtime_error(strm.str());
    }
}