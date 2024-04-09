#pragma once
#include <glm/ext.hpp>

struct Collision
{
	bool x, y, z;
};

class ICollisionProvider
{
public:
	virtual Collision GetCollision(glm::dvec3 point) const = 0;
};