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