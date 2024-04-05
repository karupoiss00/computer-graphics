#pragma once
#include "pch.h"

class Camera
{
public:
	explicit Camera(double distanceToOrigin);

	void Rotate(double xAngleRadians, double yAngleRadians);
	void UpdateView();
private:
	glm::dmat4x4 m_cameraMatrix;
};