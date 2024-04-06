#include <random>
#include "pch.h"
#include "World.h"

constexpr unsigned WORLD_SIZE = 16;

World::World()
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 20);

	for (unsigned i = 0; i < WORLD_SIZE; i++)
	{
		std::vector<glm::vec3> line;
		for (unsigned j = 0; j < WORLD_SIZE; j++)
		{
			line.push_back(glm::vec3(0.31, 0.5 + dist6(rng) * 0.01, 0.13));
		}
		m_floor.push_back(line);
	}
}

std::vector<std::vector<glm::vec3>> World::GetFloor()
{
	return m_floor;
}