#pragma once
#include <vector>
#include "PhysicalObject.h"
#include "CollisionProvider.h"
#include "Marker.h"

enum class MaterialType
{
	BRICK = 1,
	BRICK_LIANE,
	STONE,
	STONE_LIANE,
	BRICK_CRACKED,
	BRICK_CHISELED,
	BRICK_SMOOTHED,
	MARKER,
	SANDSTONE,
};

struct Cell
{
	bool filled;
	MaterialType material;
};

class World : public ICollisionProvider
{
	
public:
	World();

	std::vector<std::vector<Cell>> GetMap();
	std::vector<PhysicalObject*> GetObjects();

	CollisionData GetCollision(Collision::BoundingBox box) const override;

	Marker const& GetMarker() const;
private:
	double GetClampX(Collision::BoundingBox objectBox) const;
	double GetClampZ(Collision::BoundingBox objectBox) const;

	std::vector<std::vector<Cell>> m_map;
	Marker m_marker;
};