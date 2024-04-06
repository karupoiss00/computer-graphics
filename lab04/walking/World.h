#pragma once
#include <vector>

class World
{
public:
	World();
	std::vector<std::vector<glm::vec3>> GetFloor();
private:
	std::vector<std::vector<glm::vec3>> m_floor;
};