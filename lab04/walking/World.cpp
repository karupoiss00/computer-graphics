#include <random>
#include <iostream>
#include "pch.h"
#include "World.h"

constexpr unsigned WORLD_SIZE = 18;
constexpr unsigned BLOCK_SIZE = 1;
constexpr double COLLISION_THRESHOLD = 0.3;

const std::vector<std::vector<bool>> LABYRINTH_MAP = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};


World::World()
{
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

Collision World::GetCollision(glm::dvec3 point) const
{
	size_t playerX = static_cast<size_t>(point.x);
	size_t playerZ = static_cast<size_t>(point.z);
	double playerMinX, playerMaxX, playerMinZ, playerMaxZ;

	std::modf(point.x + COLLISION_THRESHOLD, &playerMaxX);
	std::modf(point.x - COLLISION_THRESHOLD, &playerMinX);
	std::modf(point.z + COLLISION_THRESHOLD, &playerMaxZ);
	std::modf(point.z - COLLISION_THRESHOLD, &playerMinZ);

	return Collision{
		!m_map[playerMinX][playerZ].filled && !m_map[playerMaxX][playerZ].filled,
		true,
		!m_map[playerX][playerMinZ].filled && !m_map[playerX][playerMaxZ].filled,
	};
}

std::vector<std::vector<Cell>> World::GetMap()
{
	return m_map;
}