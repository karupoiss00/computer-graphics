#pragma once
#include <map>
#include "Direction.h"
#include "CollisionProvider.h"
#include "PhysicalObject.h"

class Player : public PhysicalObject
{
public:
	Player(IViewDirectionProvider& viewProvider);

	void Jump(double speed = 1.0);
	void SetForwardMovement(double speed = 1.0);
	void SetBackwardMovement(double speed = 1.0);
	void SetStrafeLeftMovement(double speed = 1.0);
	void SetStrafeRightMovement(double speed = 1.0);

	void Update();
private:
	void RecalculateVelocity();

	IViewDirectionProvider& m_viewProvider;
	std::map<Direction, double> m_moving;
};