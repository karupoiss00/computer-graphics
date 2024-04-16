#include <random>
#include <iostream>
#include "pch.h"
#include "World.h"

constexpr unsigned WORLD_SIZE = 18;
constexpr double COLLISION_THRESHOLD = 0.1;

World::World()
{
	std::vector<std::vector<bool>> LABYRINTH_MAP = {
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
		{1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1},
		{1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0, 1},
		{1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1},
		{1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
		{1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1},
		{1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1},
		{1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1},
		{1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 1},
		{1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0, 1},
		{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1},
		{1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 1},
		{1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
		{1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1},
		{1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
		{1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	};


	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_real_distribution<> dist6(0.1, 0.2);

	for (unsigned i = 0; i < WORLD_SIZE; i++)
	{
		std::vector<Cell> line;
		for (unsigned j = 0; j < WORLD_SIZE; j++)
		{
			auto color = glm::vec3(0.4, 0.1 + dist6(rng), 0.1);
			line.push_back(Cell{ LABYRINTH_MAP[i][j] == 1, color });
		}
		m_map.push_back(line);
	}
}

Collision World::GetCollision(BoundingBox box, glm::dvec3 delta) const
{
	glm::dvec3 clamp(0, 0, 0);

	auto newY = box.position.y - box.size.y / 2 + delta.y;

	auto newX = size_t(box.position.x + delta.x + box.size.x / 2 * (delta.x < 0 ? -1 : +1));
	bool hasXCollision = m_map[newX][size_t(box.position.z)].filled;
	if (hasXCollision && newY < 1)
	{
		clamp.x = -delta.x;
	}

	auto newZ = size_t(box.position.z + delta.z + box.size.z / 2 * (delta.z < 0 ? -1 : +1));
	bool hasZCollision = m_map[size_t(box.position.x)][newZ].filled;
	if (hasZCollision && newY < 1)
	{
		clamp.z = -delta.z;
	}

	auto minHeight = hasZCollision || hasXCollision ? 1.0 : 0.0;
	if (newY < minHeight)
	{
		clamp.y = -delta.y;
	}

	return Collision{ clamp };
}

std::vector<std::vector<Cell>> World::GetMap()
{
	return m_map;
}