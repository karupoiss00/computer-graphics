#pragma once
#include "Renderable.h"
#include "World.h"

class WorldRenderer : public IRenderable
{
public:
	WorldRenderer(World& world);
	void Render() const;
private:
	void DrawSquare(int x, int z) const;
	void DrawColumn(int x, int z) const;

	World& m_world;
};