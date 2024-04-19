#pragma once
#include "Renderable.h"
#include "CubemapTexture.h"

class SkyBox : public IRenderable
{
public:
	SkyBox(float size, CubemapTexture& texture);

	void SetPosition(glm::dvec3 position);

	void Render() const override;
private:
	CubemapTexture& m_texture;
	float m_size;
	glm::dvec3 m_position;
};