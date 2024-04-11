#include "pch.h"
#include "PlayerController.h"

PlayerController::PlayerController(Player& player, Camera& camera, ICollisionProvider& collisionProvider)
	: m_player(player)
	, m_camera(camera)
	, m_collisionProvider(collisionProvider)
{}

void PlayerController::Update(double deltaTime)
{
	m_player.Update(deltaTime, m_camera);
	auto newPosition = m_player.GetPosition();
	m_camera.SetPosition(newPosition);
}