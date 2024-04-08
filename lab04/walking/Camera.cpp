#include "pch.h"
#include "Camera.h"

constexpr float ROTATION_SPEED = 0.003f;
constexpr glm::dvec3 UP_DIRECTION = { 0.0, 1.0, 0.0 };

Camera::Camera()
	: m_cameraPos(glm::dvec3{ 0.0, 0.0, 0.0 })
	, m_lookDirection(glm::normalize(glm::dvec3{ 1.0, 0.0, 1.0 }))
{}

void Camera::Rotate(double deltaX, double deltaY)
{
	auto mouseDelta = glm::dvec2{ deltaX, deltaY };

	glm::dvec3 toRotateAround = glm::cross(m_lookDirection, UP_DIRECTION);
	glm::dmat4 rotator = glm::rotate(-mouseDelta.x * ROTATION_SPEED, UP_DIRECTION)
					  * glm::rotate(-mouseDelta.y * ROTATION_SPEED, toRotateAround);

	m_lookDirection = glm::mat3(rotator) * m_lookDirection;
}

void Camera::SetPosition(glm::dvec3 position)
{
	m_cameraPos = position;
}

glm::dmat4 Camera::GetWorldToViewMatrix() const
{
	return glm::lookAt(
		m_cameraPos,
		m_cameraPos + glm::normalize(m_lookDirection),
		UP_DIRECTION
	);
}

glm::dvec3 Camera::GetDirectionProjection(Direction dir)
{
	switch (dir)
	{
	case Direction::FORWARD:
		return glm::dvec3{ m_lookDirection.x, 0, m_lookDirection.z };
	case Direction::BACKWARD:
		return -glm::dvec3{ m_lookDirection.x, 0, m_lookDirection.z };
	case Direction::LEFT:
		return -glm::cross(m_lookDirection, UP_DIRECTION);
	case Direction::RIGHT:
		return glm::cross(m_lookDirection, UP_DIRECTION);
	}

	throw std::exception("unknown direction");
}