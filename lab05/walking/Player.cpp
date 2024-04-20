#include <iostream>
#include "pch.h"
#include "Math.h"
#include "ViewDirectionProvider.h"
#include "Player.h"

constexpr double ELASTICITY = 0;
constexpr double BUNNY_HOP_ACCELERATION = 1.05;
constexpr double MAX_FORWARD_SPEED = 10;
constexpr glm::dvec3 START_PLAYER_POSITION = { 9.5, 0.5, 8.5 };
constexpr glm::dvec3 PLAYER_SIZE = { 0.2, 1.0, 0.2 };

Player::Player(IViewDirectionProvider& viewProvider)
	: PhysicalObject({
		START_PLAYER_POSITION,
		PLAYER_SIZE
	}, 1.0)
	, m_viewProvider(viewProvider)
	, m_jumpingSpeed(3)
{
	m_moving = {
		{Direction::FORWARD, 0},
		{Direction::BACKWARD, 0},
		{Direction::LEFT, 0},
		{Direction::RIGHT, 0},
	};
}

void Player::SetJumpingSpeed(double speed)
{
	m_jumpingSpeed = speed;
}


void Player::SetJumping(bool jumping)
{
	m_jumping = jumping;

	auto velocity = GetVelocity();
	auto forwardSpeed = m_moving[Direction::FORWARD];
	if (m_jumping && IsEqual(velocity.y, 0) && !IsEqual(forwardSpeed, 0))
	{
		m_moving[Direction::FORWARD] = 5;
	}

	RecalculateVelocity();
}

void Player::SetForwardMovement(double speed)
{
	m_moving[Direction::FORWARD] = speed;

	RecalculateVelocity();
}
void Player::SetBackwardMovement(double speed)
{
	m_moving[Direction::BACKWARD] = speed;

	RecalculateVelocity();
}

void Player::SetStrafeLeftMovement(double speed)
{
	m_moving[Direction::LEFT] = speed;

	RecalculateVelocity();
}

void Player::SetStrafeRightMovement(double speed)
{
	m_moving[Direction::RIGHT] = speed;

	RecalculateVelocity();
}

void Player::RecalculateVelocity()
{
	auto velocity = GetVelocity();
	glm::dvec3 newVelocity(0, velocity.y, 0);

	for (auto [direction, speed] : m_moving)
	{
		auto dirVelocity = m_viewProvider.GetDirectionProjection(direction) * speed;
		newVelocity += dirVelocity;
	}

	if (m_jumping && IsEqual(velocity.y, 0))
	{
		newVelocity.y = m_jumpingSpeed;
	}

	SetVelocity(newVelocity);
}

void Player::Update()
{
	RecalculateVelocity();
}

bool Player::IsJumping() const
{
	return m_jumping;
}