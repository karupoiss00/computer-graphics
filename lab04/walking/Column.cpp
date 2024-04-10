#include "pch.h"
#include "Column.h"

Column::Column(glm::dvec3 pos, float height)
	: m_height(height)
	, m_pos(pos)
{}

void Column::Draw() const
{
	static constexpr float vertices[8][3] = {
		{ -1, 0, -1 }, // 0
		{ +1, 0, -1 }, // 1
		{ +1, +1, -1 }, // 2
		{ -1, +1, -1 }, // 3
		{ -1, 0, +1 }, // 4
		{ +1, 0, +1 }, // 5
		{ +1, +1, +1 }, // 6
		{ -1, +1, +1 }, // 7
	};

	static constexpr unsigned char faces[6][4] = {
		{ 4, 7, 3, 0 },
		{ 5, 1, 2, 6 },
		{ 4, 0, 1, 5 },
		{ 7, 6, 2, 3 },
		{ 0, 3, 2, 1 },
		{ 4, 5, 6, 7 },
	};
	static size_t const faceCount = sizeof(faces) / sizeof(*faces);

	glPushMatrix();
	glTranslated(m_pos.x, m_pos.y, m_pos.z);
	glScalef(0.5f, m_height, 0.5f);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.5f);
	glBegin(GL_QUADS);
	{
		for (size_t face = 0; face < faceCount; ++face)
		{
			for (size_t i = 0; i < 4; ++i)
			{
				size_t vertexIndex = faces[face][i];
				glVertex3fv(vertices[vertexIndex]);
			}
		}
	}
	glEnd();

	glPopMatrix();
}