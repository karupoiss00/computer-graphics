#include "pch.h"
#include "Canabola.h"
#include "Shader.h"
#include "ShaderLoader.h"
#include "ShaderCompiler.h"
#include "ProgramLinker.h"
#include "Program.h"
#include "ProgramInfo.h"

Canabola::Canabola(float size, glm::dvec3 pos)
	: ObjectWithShader(L"./shaders/kanabola.vsh")
	, m_size(size)
	, m_position(pos)
{

}

void Canabola::RenderObject() const
{
	glPushMatrix();

	glTranslated(m_position.x, m_position.y, m_position.z);
	glScaled(m_size, m_size, m_size);

	glBegin(GL_LINE_LOOP);
	{
		for (double i = 0; i < 2 * M_PI; i += M_PI / 1000)
		{
			glVertex3d(i, 0, 0);
		}
	}
	glEnd();

	glPopMatrix();
}

void Canabola::SetObjectSize(float size)
{
	m_size = size;
}
