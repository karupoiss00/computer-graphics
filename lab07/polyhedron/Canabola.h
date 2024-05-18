#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Program.h"
#include "Renderable.h"

class Canabola : public IRenderable
{
public:
	explicit Canabola(float size = 1, glm::dvec3 pos = { 0, 0, 0 });
	void Render() const;
	void Reload();

	void SetObjectSize(float size);
private:
	void SetupShaders() const;

	float m_size;
	glm::dvec3 m_position;

	mutable Program m_program;
	mutable bool m_shadersLoaded;
};