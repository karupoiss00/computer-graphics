#include "pch.h"
#include "CameraController.h"

CameraController::CameraController(Camera& cam)
	: m_camera(cam)
{

}

void CameraController::MouseMoveHandler(glm::ivec2 windowSize, double x, double y, bool movePrevented)
{
	const glm::dvec2 mousePos{ x, y };

	if (!m_mousePos.has_value())
	{
		m_mousePos = mousePos;
	}

	if (!movePrevented)
	{
		m_camera.Rotate(x - m_mousePos->x, y - m_mousePos->y);
	}
	
	m_mousePos = mousePos;
}