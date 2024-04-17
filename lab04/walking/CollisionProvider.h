#pragma once
#include "Collision.h"

class ICollisionProvider
{
public:
	virtual Collision GetCollision(BoundingBox box) const = 0;
	
	virtual ~ICollisionProvider() = default;
};