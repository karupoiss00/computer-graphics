#pragma once
#include <map>
#include "Direction.h"
#include "CollisionProvider.h"
#include "GravityObject.h"

class Player : public IGravityObject
{
public:
	Player(ICollisionProvider& collisionProvider);

	void Jump();
	void SetVerticalSpeed(double speed) override;
	void SetPosition(glm::dvec3 position);
	void SetSpeed(Direction dir, double speed);	
	void Update(double deltaTime, IViewDirectionProvider& directionProvider);


	double GetVerticalSpeed() override;
	bool CanDrop() override;
	double GetElasticity() override;
	glm::dvec3 GetPosition() const;

private:
	glm::dvec3 m_position;
	std::map<Direction, double> m_speed;
	ICollisionProvider& m_collisionProvider;
};