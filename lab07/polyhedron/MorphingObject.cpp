#include "pch.h"
#include "MorphingObject.h"
#include "Shader.h"
#include "ShaderLoader.h"
#include "ShaderCompiler.h"
#include "ProgramLinker.h"
#include "Program.h"
#include "ProgramInfo.h"

constexpr float MORPH_PERIOD = 1.0f;

MorphingObject::MorphingObject(float size, glm::dvec3 pos)
	: ObjectWithShader(L"./shaders/morphing.vsh")
	, m_size(size)
	, m_position(pos)
	, m_morphStep(0)
{

}

void MorphingObject::RenderObject() const
{
	glUniform1f(m_program.GetUniformLocation("phase"), m_morphStep);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glPushMatrix();

	glTranslated(m_position.x, m_position.y, m_position.z);
	glScaled(m_size, m_size, m_size);

	float x = 0;
	float y = 0;
	float z = 0;

	float u = 0;
	float v = 0;

	glBegin(GL_TRIANGLE_STRIP);
	for (v = 0; v <= 1; v += 0.01f)
	{
		for (u = 0; u <= 1; u += 0.01f)
		{
			glVertex3f(u, v, z);
			glColor3f(u, v, z);
		}
	}
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	for (u = 0; u <= 1; u += 0.01f)
	{
		for (v = 0; v <= 1; v += 0.01f)
		{
			glVertex3f(u, v, z);
			glColor3f(u, v, z);
		}
	}
	glEnd();

	glPopMatrix();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void MorphingObject::SetObjectSize(float size)
{
	m_size = size;
}

void MorphingObject::SetMorphStep(float step)
{
	step = std::fmod(step, MORPH_PERIOD * 2.0f);

	if (step >= MORPH_PERIOD) 
	{
		m_morphStep = MORPH_PERIOD - std::fmod(step, MORPH_PERIOD);
	}
	else
	{
		m_morphStep = std::fmod(step, MORPH_PERIOD);
	}
}
