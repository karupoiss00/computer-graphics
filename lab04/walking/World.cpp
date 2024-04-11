#include <random>
#include <iostream>
#include "pch.h"
#include "World.h"

constexpr unsigned WORLD_SIZE = 18;
constexpr double COLLISION_THRESHOLD = 0.01;

const CollisionFlags NO_COLLISION = {
	true,
	true,
	true
};

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

CollisionFlags World::GetCollision(glm::dvec3 point) const
{
	size_t playerX = static_cast<size_t>(point.x);
	size_t playerZ = static_cast<size_t>(point.z);

	double playerMinX, playerMaxX, playerMinZ, playerMaxZ, fractional;

	fractional = std::modf(point.x + COLLISION_THRESHOLD, &playerMaxX);
	fractional = std::modf(point.x - COLLISION_THRESHOLD, &playerMinX);
	fractional = std::modf(point.z + COLLISION_THRESHOLD, &playerMaxZ);
	fractional = std::modf(point.z - COLLISION_THRESHOLD, &playerMinZ);

	size_t playerMinXsz = static_cast<size_t>(playerMinX);
	size_t playerMaxXsz = static_cast<size_t>(playerMaxX);
	size_t playerMinZsz = static_cast<size_t>(playerMinZ);
	size_t playerMaxZsz = static_cast<size_t>(playerMaxZ);

	try
	{
		return CollisionFlags{
			!m_map[playerMinXsz][playerZ].filled && !m_map[playerMaxXsz][playerZ].filled,
			point.y > 0,
			!m_map[playerX][playerMinZsz].filled && !m_map[playerX][playerMaxZsz].filled,
		};
	}
	catch (...)
	{
		return NO_COLLISION;
	}
}

std::vector<std::vector<Cell>> World::GetMap()
{
	return m_map;
}