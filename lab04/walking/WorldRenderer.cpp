#include <iostream>
#include "pch.h"
#include "Column.h"
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
	
	auto map = m_world.GetMap();

	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[i].size(); j++)
		{
			auto cell = map[i][j];
			auto color = cell.color;
			glColor4f(color.x, color.y, color.z, 1);
			if (cell.filled)
			{
				DrawColumn(i, j);
			}
			else
			{
				DrawSquare(i, j);
			}
		}
	}
}

void WorldRenderer::DrawSquare(int x, int z) const
{
	glPushMatrix();
	glTranslated(x + 0.5, 0, z + 0.5);
	glScaled(0.5, 0.5, 0.5);

	glBegin(GL_POLYGON);
	glVertex3d(-1, 0, -1);
	glVertex3d(-1, 0, 1);
	glVertex3d(1, 0, 1);
	glVertex3d(1 , 0, -1);
	glEnd();
	glPopMatrix();
}

void WorldRenderer::DrawColumn(int x, int z) const
{
	Column column({x + 0.5, 0, z + 0.5});
	column.Draw();
}
