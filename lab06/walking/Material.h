#pragma once

#include "pch.h"

class Material
{
public:
	Material();

	void SetDiffuse(GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1);
	void SetAmbient(GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1);
	void SetSpecular(GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1);
	void SetShininess(GLfloat shininess);
	void Activate(GLenum side = GL_FRONT) const;
private:
	GLfloat m_shininess;
	GLfloat m_diffuse[4];
	GLfloat m_specular[4];
	GLfloat m_ambient[4];
};