#include "pch.h"
#include "PlayerController.h"

PlayerController::PlayerController(Player& player, Camera& camera, ICollisionProvider& collisionProvider)
	: m_player(player)
	, m_camera(camera)
	, m_collisionProvider(collisionProvider)
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
		auto positionDelta = moveVector * speed * deltaTime;
		
		auto collision = m_collisionProvider.GetCollision(playerPos + positionDelta);

		positionDelta.x *= static_cast<double>(collision.x);
		positionDelta.y *= static_cast<double>(collision.y);
		positionDelta.z *= static_cast<double>(collision.z);

		auto newPosition = playerPos + positionDelta;
		m_player.SetPosition(newPosition);
		m_camera.SetPosition(newPosition);
	}
}