#include "pch.h"
#include "Dodecahedron.h"

constexpr unsigned FACES_COUNT = 12;
constexpr unsigned VERTECES_COUNT = 20;
constexpr unsigned VERTECIES_ON_SIDE_COUNT = 5;
constexpr float VERTICES[VERTECES_COUNT][3] = {
	{1, 1, 1},
	{1, 1, -1},
	{1, -1, 1},
	{1, -1, -1},
	{-1, 1, 1},
	{-1, 1, -1},
	{-1, -1, 1},
	{-1, -1, -1},
	{0, 0.618, 1.618},
	{0, 0.618, -1.618},
	{0, -0.618, 1.618},
	{0, -0.618, -1.618},
	{0.618, 1.618, 0},
	{0.618, -1.618, 0},
	{-0.618, 1.618, 0},
	{-0.618, -1.618, 0},
	{1.618, 0, 0.618},
	{1.618, 0, -0.618},
	{-1.618, 0, 0.618},
	{-1.618, 0, -0.618}
};

/*
	TOP_TOP,
	TOP_FIRST,
	TOP_SECOND,
	TOP_THIRD,
	TOP_FOURTH,
	TOP_FIFTH,
	BOTTOM_BOTTOM,
	BOTTOM_FIRST,
	BOTTOM_SECOND,
	BOTTOM_THIRD,
	BOTTOM_FOURTH,
	BOTTOM_FIFTH,
*/
constexpr unsigned char FACES[FACES_COUNT][VERTECIES_ON_SIDE_COUNT] = {
	{12, 14, 4, 8, 0},   // TOP_TOP
	{8, 10, 2, 16, 0},   // TOP_FIRST
	{16, 17, 1, 12, 0},  // TOP_SECOND
	{9, 5, 14, 12, 1},   // TOP_THIRD
	{14, 5, 19, 18, 4},  // TOP_FOURTH
	{18, 6, 10, 8, 4},   // TOP_FIFTH
	{13, 15, 7, 11, 3},  // BOTTOM_BOTTOM
	{10, 6, 15, 13, 2},  // BOTTOM_FIRST
	{13, 3, 17, 16, 2},  // BOTTOM_SECOND
	{17, 3, 11, 9, 1},   // BOTTOM_THIRD
	{9, 11, 7, 19, 5},   // BOTTOM_FOURTH
	{6, 18, 19, 7, 15}   // BOTTOM_FIFTH
};

Dodecahedron::Dodecahedron(float size)
	: m_size(size)
{
	constexpr glm::vec4 defaultColor{ 1, 1, 1, 1 };
	SetSideColor(DodecahedronSide::TOP_TOP, defaultColor);
	SetSideColor(DodecahedronSide::TOP_FIRST, defaultColor);
	SetSideColor(DodecahedronSide::TOP_SECOND, defaultColor);
	SetSideColor(DodecahedronSide::TOP_THIRD, defaultColor);
	SetSideColor(DodecahedronSide::TOP_FOURTH, defaultColor);
	SetSideColor(DodecahedronSide::TOP_FIFTH, defaultColor);
	SetSideColor(DodecahedronSide::BOTTOM_BOTTOM, defaultColor);
	SetSideColor(DodecahedronSide::BOTTOM_FIRST, defaultColor);
	SetSideColor(DodecahedronSide::BOTTOM_SECOND, defaultColor);
	SetSideColor(DodecahedronSide::BOTTOM_THIRD, defaultColor);
	SetSideColor(DodecahedronSide::BOTTOM_FOURTH, defaultColor);
	SetSideColor(DodecahedronSide::BOTTOM_FIFTH, defaultColor);
}

void Dodecahedron::Draw() const
{
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, glm::value_ptr(m_specularColor));
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, m_shininess);


	for (size_t face = 0; face < FACES_COUNT; ++face)
	{
		const unsigned char* facePoints = FACES[face];
		glColor4fv(glm::value_ptr(m_sideColors[face]));

		auto p0 = glm::make_vec3(VERTICES[facePoints[0]]);
		auto p1 = glm::make_vec3(VERTICES[facePoints[1]]);
		auto p2 = glm::make_vec3(VERTICES[facePoints[2]]);
		auto v01 = p1 - p0;
		auto v02 = p2 - p0;
		auto normal = glm::normalize(glm::cross(v01, v02));

		glNormal3fv(glm::value_ptr(normal));

		glBegin(GL_TRIANGLE_FAN);
		for (int x = 0; x < 5; x++)
		{
			auto p = glm::make_vec3(VERTICES[facePoints[x]]);
			p *= m_size * 0.5f;
			glVertex3fv(glm::value_ptr(p));
		}
		glEnd();

		glColor4fv(glm::value_ptr(m_sideColors[face]));

		glBegin(GL_LINE_STRIP);
		for (int x = 0; x < 5; x++)
		{
			auto p = glm::make_vec3(VERTICES[facePoints[x]]);
			p *= m_size * 0.5f;
			glVertex3fv(glm::value_ptr(p));
		}
		auto p = glm::make_vec3(VERTICES[facePoints[0]]);
		p *= m_size * 0.5f;
		glVertex3fv(glm::value_ptr(p));
		glEnd();
	}
}

void Dodecahedron::SetSideColor(DodecahedronSide side, const glm::vec4& color)
{
	unsigned index = static_cast<unsigned>(side);
	m_sideColors[index] = color;
}

void Dodecahedron::SetSpecularColor(glm::vec4 color)
{
	m_specularColor = color;
}

void Dodecahedron::SetShininess(float shininess)
{
	m_shininess = shininess;
}