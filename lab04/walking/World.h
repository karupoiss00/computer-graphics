#pragma once
#include <vector>
#include "PhysicalObject.h"
#include "CollisionProvider.h"
#include "Marker.h"

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
	std::vector<PhysicalObject*> GetObjects();

	Collision GetCollision(BoundingBox box) const override;

	Marker const& GetMarker() const;
private:
	double GetClampX(BoundingBox objectBox) const;
	double GetClampZ(BoundingBox objectBox) const;

	std::vector<std::vector<Cell>> m_map;
	Marker m_marker;
};