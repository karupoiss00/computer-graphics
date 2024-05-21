#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "ObjectWithShader.h"

class Flag : public ObjectWithShader<GL_FRAGMENT_SHADER>
{
public:
	explicit Flag(float size = 1, glm::dvec3 pos = { 0, 0, 0 });

	void SetObjectSize(float size);
protected:
	void RenderObject() const override;
private:
	float m_size;
	glm::dvec3 m_position;
};