#pragma once
#include "Camera.h"

class CameraController
{
public:
	CameraController(Camera& cam);
	void MouseMoveHandler(glm::ivec2 windowSize, double x, double y, bool movePrevented);
private:
	Camera& m_camera;
	glm::dvec2 m_mousePos = {};
};