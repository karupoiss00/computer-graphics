#include <random>
#include <iostream>
#include "pch.h"
#include "World.h"
#include "Math.h"

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

double World::GetClampX(BoundingBox objectBox) const
{
	double minX = objectBox.position.x - objectBox.size.x / 2;
	auto const& minXCell = m_map[size_t(minX)][size_t(objectBox.position.z)];
	if (minXCell.filled)
	{
		return double(size_t(minX)) + 1 - minX;
	}

	double maxX = objectBox.position.x + objectBox.size.x / 2;
	auto const&  maxXCell = m_map[size_t(maxX)][size_t(objectBox.position.z)];
	if (maxXCell.filled)
	{
		return double(size_t(maxX)) - maxX;
	}

	return 0;
}

double World::GetClampZ(BoundingBox objectBox) const
{
	double minZ = objectBox.position.z - objectBox.size.z / 2;
	auto zLine = m_map[size_t(objectBox.position.x)];

	auto const& minZCell = zLine[size_t(minZ)];
	if (minZCell.filled)
	{
		return double(size_t(minZ)) + 1 - minZ;
	}

	double maxZ = objectBox.position.z + objectBox.size.z / 2;
	auto const& maxZCell = zLine[size_t(maxZ)];
	if (maxZCell.filled)
	{
		return double(size_t(maxZ)) - maxZ;
	}

	return 0;
}

Collision World::GetCollision(BoundingBox box) const
{
	glm::dvec3 clamp(GetClampX(box), 0, GetClampZ(box));
	auto newY = box.position.y - box.size.y / 2;

	if (newY < 0)
	{
		clamp.y = -newY;
	}

	return Collision{ clamp };
}

std::vector<std::vector<Cell>> World::GetMap()
{
	return m_map;
}

std::vector<PhysicalObject*> World::GetObjects()
{
	return {&m_marker};
}

Marker const& World::GetMarker() const
{
	return m_marker;
}