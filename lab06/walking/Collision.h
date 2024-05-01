#pragma once
#include <glm/ext.hpp>

struct CollisionData
{
	glm::dvec3 clamp;
};

namespace Collision
{
	struct BoundingBox
	{
		glm::dvec3 position;
		glm::dvec3 size;
	};
}