#include "pch.h"
#include "Flag.h"
#include "Shader.h"
#include "ShaderLoader.h"
#include "ShaderCompiler.h"
#include "ProgramLinker.h"
#include "Program.h"
#include "ProgramInfo.h"

Flag::Flag(float size, glm::dvec3 pos)
	: ObjectWithShader(L"./shaders/flag.fsh")
	, m_size(size)
	, m_position(pos)
{

}


void Flag::RenderObject() const
{
	glPushMatrix();

	glTranslated(-0.75, -0.5, 0);
	glTranslated(m_position.x, m_position.y, m_position.z);
	glScaled(m_size, m_size, m_size);

	const static double VERTEXES[8][3] = {
		{1.5, 0, 0},
		{1.5, 1, 0},
		{0, 1, 0},
		{0, 0, 0},

		{0, 0, 0},
		{0, 1, 0},
		{1.5, 1, 0},
		{1.5, 0, 0},
	};

	const static double TEXTURE_VERTEXES[8][2] = {
		{1.5, 0},
		{1.5, 1},
		{0, 1},
		{0, 0},

		{0, 0},
		{0, 1},
		{1.5, 1},
		{1.5, 0},
	};

	glBegin(GL_QUADS);
	{
		for (int i = 0; i < 8; i++)
		{
			glTexCoord2dv(TEXTURE_VERTEXES[i]);
			glVertex3dv(VERTEXES[i]);
		}
	}
	glEnd();

	glPopMatrix();
}

void Flag::SetObjectSize(float size)
{
	m_size = size;
}
