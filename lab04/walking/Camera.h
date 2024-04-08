#pragma once
#include "Direction.h"

class Camera
{
public:
	explicit Camera();

	void Rotate(double mouseX, double mouseY);

	void SetPosition(glm::dvec3 position);

	glm::dvec3 GetDirectionProjection(Direction dir);

	glm::dmat4 GetWorldToViewMatrix() const;
private:
	glm::dvec3 m_cameraPos;
	glm::dvec3 m_lookDirection;
};