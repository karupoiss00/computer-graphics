#include <algorithm>
#include "pch.h"
#include "Camera.h"

constexpr double MIN_VERTICAL_ANGLE = 30;
constexpr double MAX_VERTICAL_ANGLE = 150;
constexpr float ROTATION_SPEED = 0.003f;
constexpr glm::dvec3 UP_DIRECTION = { 0.0, 1.0, 0.0 };

Camera::Camera()
	: m_cameraPos(glm::dvec3{ 0.0, 0.0, 0.0 })
	, m_lookDirection(glm::normalize(glm::dvec3{ 1.0, 0, 1.0 }))
{}

void Camera::Rotate(double deltaX, double deltaY)
{
	auto mouseDelta = glm::dvec2{ deltaX, deltaY };

	auto deltaAngleRad = -mouseDelta.y * ROTATION_SPEED;
	auto deltaAngle = -deltaAngleRad / M_PI * 180;
	auto currentAngle = glm::angle(m_lookDirection, UP_DIRECTION) / M_PI * 180;
	auto newAngle = currentAngle + deltaAngle;

	double verticalAngle = 0;

	if ((deltaAngle > 0 && newAngle < MAX_VERTICAL_ANGLE) || (deltaAngle < 0 && newAngle > MIN_VERTICAL_ANGLE))
	{
		verticalAngle = deltaAngleRad;
	}

	glm::dvec3 toRotateAround = glm::cross(m_lookDirection, UP_DIRECTION);
	glm::dmat4 rotator = glm::rotate(-mouseDelta.x * ROTATION_SPEED, UP_DIRECTION)
					  * glm::rotate(verticalAngle, toRotateAround);

	m_lookDirection = glm::normalize(glm::mat3(rotator) * m_lookDirection);
}

void Camera::SetPosition(glm::dvec3 position)
{
	m_cameraPos = position;
}

glm::dmat4 Camera::GetWorldToViewMatrix() const
{
	return glm::lookAt(
		m_cameraPos,
		m_cameraPos + m_lookDirection,
		UP_DIRECTION
	);
}

glm::dvec3 Camera::GetLookDirection() const
{
	return m_lookDirection;
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

double Camera::GetVerticalAngle() const
{
	return glm::angle(m_lookDirection, UP_DIRECTION) / M_PI * 180;
}

double Camera::GetMaxVerticalAngle() const
{
	return MAX_VERTICAL_ANGLE;
}

double Camera::GetMinVerticalAngle() const
{
	return MIN_VERTICAL_ANGLE;
}