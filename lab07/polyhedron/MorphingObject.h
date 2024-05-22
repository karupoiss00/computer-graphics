#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "ObjectWithShader.h"

class MorphingObject : public ObjectWithShader<GL_VERTEX_SHADER>
{
public:
	explicit MorphingObject(float size = 1, glm::dvec3 pos = { 0, 0, 0 });

	void SetObjectSize(float size);
	void SetMorphStep(float step);
protected:
	void RenderObject() const override;
private:
	float m_size;
	glm::dvec3 m_position;
	float m_morphStep;
};