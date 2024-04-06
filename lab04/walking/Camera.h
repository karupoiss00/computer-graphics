#pragma once
#include "pch.h"

class Camera
{
public:
	explicit Camera();

	void Rotate(double mouseX, double mouseY);

	void MoveForward(double speed);
	void MoveBackward(double speed);
	void MoveLeft(double speed);
	void MoveRight(double speed);

	void SetPosition(glm::dvec3 pos);

	glm::dmat4 GetWorldToViewMatrix() const;
private:
	glm::dvec3 m_cameraPos;
	glm::dvec3 m_lookDirection;
};