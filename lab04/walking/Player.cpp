#include <iostream>
#include "pch.h"
#include "Math.h"
#include "ViewDirectionProvider.h"
#include "Player.h"

constexpr double ELASTICITY = 0;
constexpr glm::dvec3 START_PLAYER_POSITION = { 9.5, 0.5, 8.5 };
constexpr glm::dvec3 PLAYER_SIZE = { 0.2, 1.0, 0.2 };

Player::Player(ICollisionProvider& collisionProvider)
	: m_box({
		START_PLAYER_POSITION,
		PLAYER_SIZE
	})
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
	return m_box.position;
}

void Player::SetPosition(glm::dvec3 position)
{
	m_box.position = position;
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

		auto collision = m_collisionProvider.GetCollision(m_box, positionDelta);

		m_box.position += positionDelta + collision.clamp;
	}
}

void Player::Jump()
{
	if (IsEqual(m_speed[Direction::VERTICAL], 0))
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
	auto collision = m_collisionProvider.GetCollision(m_box, { 0, -0.01, 0 });
	return IsEqual(collision.clamp.y, 0);
}

double Player::GetElasticity()
{
	return ELASTICITY;
}

void Player::SetVerticalSpeed(double speed)
{
	m_speed[Direction::VERTICAL] = speed;
}