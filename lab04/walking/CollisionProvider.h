#pragma once
#include <glm/ext.hpp>

struct CollisionFlags
{
	bool x, y, z;
};

class ICollisionProvider
{
public:
	virtual CollisionFlags GetCollision(glm::dvec3 point) const = 0;
	
	virtual ~ICollisionProvider() = default;
};