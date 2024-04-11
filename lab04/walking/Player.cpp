#include "pch.h"
#include "Math.h"
#include "ViewDirectionProvider.h"
#include "Player.h"

constexpr double ELASTICITY = 0.0;
constexpr double PLAYER_HEIGHT = 0.4;
constexpr glm::dvec3 PLAYER_HEIGHT_V = { 0, PLAYER_HEIGHT, 0 };
constexpr glm::dvec3 EPSILON_VERTICAL_MOVE = { 0, 0.01, 0 };

Player::Player(ICollisionProvider& collisionProvider)
	: m_position(9.5, PLAYER_HEIGHT, 8.5)
	, m_collisionProvider(collisionProvider)
{
	m_speed = {
		{Direction::FORWARD, 0},
		{Direction::BACKWARD, 0},
		{Direction::LEFT, 0},
		{Direction::RIGHT, 0},
		{Direction::VERTICAL, 0}
	};
}

glm::dvec3 Player::GetPosition() const
{
	return m_position;
}

void Player::SetPosition(glm::dvec3 position)
{
	m_position = position;
}

void Player::SetSpeed(Direction dir, double speed)
{
	m_speed[dir] = speed;
}

void Player::Update(double deltaTime, IViewDirectionProvider& directionProvider)
{
	for (auto dir : DIRECTIONS)
	{
		auto speed = m_speed[dir];
		auto moveVector = directionProvider.GetDirectionProjection(dir);
		auto positionDelta = moveVector * speed * deltaTime;

		auto collision = m_collisionProvider.GetCollision(m_position - PLAYER_HEIGHT_V + positionDelta);

		positionDelta.x *= static_cast<double>(collision.x);
		positionDelta.y *= static_cast<double>(collision.y);
		positionDelta.z *= static_cast<double>(collision.z);

		m_position += positionDelta;
	}
}

void Player::Jump()
{
	if (!CanDrop())
	{
		SetSpeed(Direction::VERTICAL, 2.0);
	}
}

double Player::GetVerticalSpeed()
{
	return m_speed[Direction::VERTICAL];
}

bool Player::CanDrop()
{
	auto collision = m_collisionProvider.GetCollision(m_position - PLAYER_HEIGHT_V - EPSILON_VERTICAL_MOVE);
	return collision.y;
}

double Player::GetElasticity()
{
	return ELASTICITY;
}

void Player::SetVerticalSpeed(double speed)
{
	m_speed[Direction::VERTICAL] = speed;
}