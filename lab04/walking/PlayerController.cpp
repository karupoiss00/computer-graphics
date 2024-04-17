#include "pch.h"
#include "PlayerController.h"

PlayerController::PlayerController(Player& player, Camera& camera)
	: m_player(player)
	, m_camera(camera)
{}

void PlayerController::Update()
{
	auto newPosition = m_player.GetPosition();
	m_camera.SetPosition(newPosition);
	m_player.Update();
}