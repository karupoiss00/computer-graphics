#pragma once
#include "Collision.h"

class ICollisionProvider
{
public:
	virtual CollisionData GetCollision(Collision::BoundingBox box) const = 0;
	
	virtual ~ICollisionProvider() = default;
};