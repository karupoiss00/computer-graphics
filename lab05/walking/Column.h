#pragma once

class Column
{
public:
	explicit Column(glm::dvec3 pos, float width = 1, float height = 1);
	void Draw() const;

private:
	float m_width;
	float m_height;
	float m_vertices[8][3];
	float m_faces[6][4];
	glm::dvec3 m_pos;
};