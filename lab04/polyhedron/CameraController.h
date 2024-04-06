#pragma once
#include "Camera.h"

class CameraController
{
public:
	CameraController(Camera& cam);
	void MouseDownHandler(int button, int action, [[maybe_unused]] int mods);
	void MouseMoveHandler(glm::ivec2 windowSize, double x, double y);
private:
	Camera& m_camera;

	bool m_leftButtonPressed = false;
	glm::dvec2 m_mousePos = {};
};