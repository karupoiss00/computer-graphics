#pragma once
#include <glm/glm.hpp>

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
};

struct TexturedVertex : public Vertex
{
	glm::vec2 texCoord;
};