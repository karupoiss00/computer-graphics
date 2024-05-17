#include "CameraController.h"

CameraController::CameraController(Camera& cam)
	: m_camera(cam)
{

}

void CameraController::MouseDownHandler(int button, int action, [[maybe_unused]] int mods)
{
	if (button == GLFW_MOUSE_BUTTON_1)
	{
		m_leftButtonPressed = (action & GLFW_PRESS) != 0;
	}
}

void CameraController::MouseMoveHandler(glm::ivec2 windowSize, double x, double y)
{
	const glm::dvec2 mousePos{ x, y };
	if (m_leftButtonPressed)
	{
		const auto mouseDelta = mousePos - m_mousePos;
		const double xAngle = mouseDelta.y * M_PI / windowSize.y;
		const double yAngle = mouseDelta.x * M_PI / windowSize.x;
		m_camera.Rotate(xAngle, yAngle);
	}
	m_mousePos = mousePos;
}