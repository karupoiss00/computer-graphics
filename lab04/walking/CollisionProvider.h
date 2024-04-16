#pragma once
#include <glm/ext.hpp>

struct Collision
{
	glm::dvec3 clamp;
};

struct BoundingBox
{
	glm::dvec3 position;
	glm::dvec3 size;
};

class ICollisionProvider
{
public:
	virtual Collision GetCollision(BoundingBox box, glm::dvec3 delta) const = 0;
	
	virtual ~ICollisionProvider() = default;
};