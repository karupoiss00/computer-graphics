#pragma once
#include <map>
#include "ViewDirectionProvider.h"
#include "Direction.h"
#include "CollisionProvider.h"
#include "PhysicalObject.h"

class Player : public PhysicalObject
{
public:
	Player(IViewDirectionProvider& viewProvider);

	void SetJumping(bool jumping);
	void SetJumpingSpeed(double speed);
	void SetForwardMovement(double speed = 1.0);
	void SetBackwardMovement(double speed = 1.0);
	void SetStrafeLeftMovement(double speed = 1.0);
	void SetStrafeRightMovement(double speed = 1.0);

	void Update();

	bool IsJumping() const;
private:
	void RecalculateVelocity();

	IViewDirectionProvider& m_viewProvider;
	std::map<Direction, double> m_moving;
	double m_jumpingSpeed;
	bool m_jumping;
};