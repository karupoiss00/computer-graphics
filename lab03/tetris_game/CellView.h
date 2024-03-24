#pragma once
#include <GL/glut.h>
#include "Vec.h"
#include "CellData.h"
#include "IDrawable.h"

class CellView : public IDrawable
{
public:
	CellView(CellData cell, Vec2d position)
		: m_data(cell), m_pos(position)
	{}

	void Draw() 
	{
		glColor3d(0.15, 0.15, 0.15);

		if (m_data.filled)
		{
			glColor3d(m_data.color.r, m_data.color.g, m_data.color.b);
		}

		glBegin(GL_POLYGON);
		glVertex2d(m_pos.x, m_pos.y);
		glVertex2d(m_pos.x + 1, m_pos.y);
		glVertex2d(m_pos.x + 1, m_pos.y + 1);
		glVertex2d(m_pos.x, m_pos.y + 1);
		glEnd();

		glColor3d(0.0, 0.0, 0.0);
		glBegin(GL_LINES);
		glVertex2d(m_pos.x, m_pos.y);
		glVertex2d(m_pos.x + 1, m_pos.y);

		glVertex2d(m_pos.x + 1, m_pos.y);
		glVertex2d(m_pos.x + 1, m_pos.y + 1);

		glVertex2d(m_pos.x + 1, m_pos.y + 1);
		glVertex2d(m_pos.x, m_pos.y + 1);

		glVertex2d(m_pos.x, m_pos.y + 1);
		glVertex2d(m_pos.x, m_pos.y);
		glEnd();
	}
private:
	Vec2d m_pos;
	CellData m_data;
};