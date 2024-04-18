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

	Collision GetCollision(BoundingBox box) const override;

	Marker const& GetMarker() const;
private:
	double GetClampX(BoundingBox objectBox) const;
	double GetClampZ(BoundingBox objectBox) const;

	std::vector<std::vector<Cell>> m_map;
	Marker m_marker;
};