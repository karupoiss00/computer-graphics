#pragma once
#include <map>
#include "Camera.h"
#include "Player.h"
#include "CollisionProvider.h"

class PlayerController
{
public:
	PlayerController(Player& player, Camera& camera, ICollisionProvider& collisionProvider);

	void SetSpeed(Direction dir, double speed);

	void Update(double deltaTime);
private:
	ICollisionProvider& m_collisionProvider;
	Camera& m_camera;
	Player& m_player;
	std::map<Direction, double> m_speed;
};