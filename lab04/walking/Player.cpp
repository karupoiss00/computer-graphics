#include "pch.h"
#include "Player.h"

Player::Player()
	: m_position(0.0, 0.3, -0.9)
{

}

glm::dvec3 Player::GetPosition() const
{
	return m_position;
}

void Player::SetPosition(glm::dvec3 position)
{
	m_position = position;
}