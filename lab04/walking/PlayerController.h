#pragma once
#include <map>
#include "Camera.h"
#include "Player.h"

class PlayerController
{
public:
	PlayerController(Player& player, Camera& camera);

	void SetSpeed(Direction dir, double speed);

	void Update();
private:
	Camera& m_camera;
	Player& m_player;
	std::map<Direction, double> m_speed;
};