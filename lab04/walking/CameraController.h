#pragma once
#include "Camera.h"

class CameraController
{
public:
	CameraController(Camera& cam);
	void MouseMoveHandler(glm::ivec2 windowSize, double x, double y, bool movePrevented);

	void MoveForward(double speed);
	void MoveBackward(double speed);
	void MoveLeft(double speed);
	void MoveRight(double speed);
private:
	Camera& m_camera;
	glm::dvec2 m_mousePos = {};
};