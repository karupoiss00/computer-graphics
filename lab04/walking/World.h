#pragma once
#include <vector>
#include "CollisionProvider.h"

struct Cell
{
	bool filled;
	glm::vec3 color;
};

class World : public ICollisionProvider
{
	
public:
	World();

	std::vector<std::vector<Cell>> GetMap();
	CollisionFlags GetCollision(glm::dvec3 point) const override;
private:
	std::vector<std::vector<Cell>> m_map;
};