#include "CameraController.h"

CameraController::CameraController(Camera& cam)
	: m_camera(cam)
{

}

void CameraController::MouseMoveHandler(glm::ivec2 windowSize, double x, double y, bool movePrevented)
{
	const glm::dvec2 mousePos{ x, y };

	if (!movePrevented)
	{
		m_camera.Rotate(x - m_mousePos.x, y - m_mousePos.y);
	}
	
	m_mousePos = mousePos;
}

void CameraController::MoveForward(double speed)
{
	m_camera.MoveForward(speed);
}

void CameraController::MoveBackward(double speed)
{
	m_camera.MoveBackward(speed);
}

void CameraController::MoveLeft(double speed)
{
	m_camera.MoveLeft(speed);
}

void CameraController::MoveRight(double speed)
{
	m_camera.MoveRight(speed);
}