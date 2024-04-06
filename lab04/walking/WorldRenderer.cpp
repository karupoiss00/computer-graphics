#include <iostream>
#include "pch.h"
#include "WorldRenderer.h"

WorldRenderer::WorldRenderer(World& world)
	: m_world(world)
{

}

void WorldRenderer::Render() const
{
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.5);
	glNormal3f(0, 1, 0);
	
	auto floor = m_world.GetFloor();
	int floorSize = static_cast<int>(floor.size());
	int halfFloorSize = floorSize / 2;

	for (int i = -halfFloorSize; i < halfFloorSize; i++)
	{
		for (int j = -halfFloorSize; j < halfFloorSize; j++)
		{
			auto color = floor[i + halfFloorSize][j + halfFloorSize];
			glColor4f(color.x, color.y, color.z, 1);
			DrawSquare(i, j);
		}
	}
}

void WorldRenderer::DrawSquare(int x, int z) const
{
	glBegin(GL_POLYGON);
	glVertex3d(-0.5 + x, 0, -0.5 + z);
	glVertex3d(-0.5 + x, 0, 0.5 + z);
	glVertex3d(0.5 + x, 0, 0.5 + z);
	glVertex3d(0.5 + x, 0, -0.5 + z);
	glEnd();
}
