#include "pch.h"
#include "Player.h"

Player::Player()
	: m_position(9.5, 0.4, 8.5)
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