#pragma once
#include <vector>

struct Cell
{
	bool filled;
	glm::vec3 color;
};

class World
{
	
public:
	World();
	std::vector<std::vector<Cell>> GetMap();
private:
	std::vector<std::vector<Cell>> m_map;
};