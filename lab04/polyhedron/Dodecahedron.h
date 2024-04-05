#pragma once
#include "Renderable.h"

enum class DodecahedronSide
{
	TOP_TOP,
	TOP_FIRST,
	TOP_SECOND,
	TOP_THIRD,
	TOP_FOURTH,
	TOP_FIFTH,
	BOTTOM_BOTTOM,
	BOTTOM_FIRST,
	BOTTOM_SECOND,
	BOTTOM_THIRD,
	BOTTOM_FOURTH,
	BOTTOM_FIFTH,
};

class Dodecahedron : public IRenderable
{
public:
	explicit Dodecahedron(float size = 1);
	void Render() const;

	void SetObjectSize(float size);
	void SetSideColor(DodecahedronSide side, const glm::vec4& color);
	void SetSpecularColor(glm::vec4 color);
	void SetShininess(float shininess);

private:
	static const unsigned SIDES_COUNT = 12;
	float m_size;
	glm::vec4 m_sideColors[SIDES_COUNT];
	glm::vec4 m_specularColor = { 0, 0, 0, 1 };
	float m_shininess = 1;
};