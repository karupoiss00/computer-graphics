#include "pch.h"
#include "PlayerController.h"

PlayerController::PlayerController(Player& player, Camera& camera)
	: m_player(player)
	, m_camera(camera)
{
	m_speed = {
		{Direction::FORWARD, 0},
		{Direction::BACKWARD, 0},
		{Direction::LEFT, 0},
		{Direction::RIGHT, 0}
	};
}

void PlayerController::SetSpeed(Direction dir, double speed)
{
	m_speed[dir] = speed;
}

void PlayerController::Update(double deltaTime)
{
	for (auto dir : DIRECTIONS)
	{
		auto playerPos = m_player.GetPosition();
		auto speed = m_speed[dir];
		auto moveVector = m_camera.GetDirectionProjection(dir);
		auto newPosition = playerPos + moveVector * speed * deltaTime;

		m_player.SetPosition(newPosition);
		m_camera.SetPosition(newPosition);
	}
}