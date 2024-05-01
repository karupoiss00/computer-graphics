#include "pch.h"
#include "Column.h"

Column::Column(glm::dvec3 pos, float width, float height)
	: m_width(width)
	, m_height(height)
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
	static constexpr float textureCoords[6][2] = {
		{ 1, 0 },
		{ 1, 1 },
		{ 0, 1 },
		{ 0, 0 },
	};
	static size_t const faceCount = sizeof(faces) / sizeof(*faces);

	glPushMatrix();
	glTranslated(m_pos.x, m_pos.y, m_pos.z);
	glScalef(m_width / 2, m_height, m_width / 2);
	glBegin(GL_QUADS);
	{
		for (size_t face = 0; face < faceCount; ++face)
		{
			auto facesV = faces[face];
			auto p0 = glm::make_vec3(vertices[facesV[0]]);
			auto p1 = glm::make_vec3(vertices[facesV[1]]);
			auto p2 = glm::make_vec3(vertices[facesV[2]]);
			auto v01 = p1 - p0;
			auto v02 = p2 - p0;
			auto normal = glm::normalize(glm::cross(v01, v02));
			glNormal3fv(glm::value_ptr(normal));

			for (size_t i = 0; i < 4; ++i)
			{
				size_t vertexIndex = facesV[i];
				glTexCoord2fv(textureCoords[i]);
				glVertex3fv(vertices[vertexIndex]);
			}
		}
	}
	glEnd();

	glPopMatrix();
}