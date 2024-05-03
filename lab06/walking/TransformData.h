#pragma once
#include <glm/glm.hpp>

struct TransformData
{
	TransformData(glm::dvec3 position_, glm::dvec3 scale_, glm::dvec4 rotation_)
		: position(position_)
		, scale(scale_)
		, rotation(rotation_)
	{}

	glm::dvec3 position;
	glm::dvec3 scale;
	glm::dvec4 rotation;
};
