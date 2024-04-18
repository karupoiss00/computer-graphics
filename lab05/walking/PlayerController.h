#pragma once
#include <map>
#include "Camera.h"
#include "Player.h"
#include "CollisionProvider.h"

class PlayerController
{
public:
	PlayerController(Player& player, Camera& camera);

	void Update();
private:
	Camera& m_camera;
	Player& m_player;
};