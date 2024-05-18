#include "pch.h"
#include "Canabola.h"
#include "Shader.h"
#include "ShaderLoader.h"
#include "ShaderCompiler.h"
#include "ProgramLinker.h"
#include "Program.h"
#include "ProgramInfo.h"

Canabola::Canabola(float size, glm::dvec3 pos)
	: m_size(size)
	, m_position(pos)
	, m_shadersLoaded(false)
	, m_program()
{

}

void Canabola::Render() const
{
	if (!m_shadersLoaded)
	{
		SetupShaders();
	}

	glUseProgram(m_program);

	glTranslated(m_position.x, m_position.y, m_position.z);
	glScaled(m_size, m_size, m_size);

	glBegin(GL_LINES);
	{
		for (double i = 0; i < 2 * M_PI; i += M_PI / 1000)
		{
			glVertex3d(i, 0, 0);
		}
	}
	glEnd();

	glUseProgram(0);
}

void Canabola::SetObjectSize(float size)
{
	m_size = size;
}

void Canabola::Reload()
{
	m_shadersLoaded = false;
	SetupShaders();
}

void Canabola::SetupShaders() const
{
	try
	{
		ShaderLoader loader;
		Shader vertexShader = loader.LoadShader(GL_VERTEX_SHADER, L"./shaders/kanabola.vsh");

		ShaderCompiler compiler;

		compiler.CompileShader(vertexShader);

		m_program.Create();
		m_program.AttachShader(vertexShader);

		compiler.CheckStatus();

		ProgramLinker linker;

		linker.LinkProgram(m_program);
		linker.CheckStatus();

		ProgramInfo info(m_program);
		info.Print(std::cout);
	}
	catch (std::exception const& e)
	{
		std::cout << e.what() << std::endl;
	}

	m_shadersLoaded = true;
}