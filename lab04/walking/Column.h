#pragma once

enum class CubeSide
{
	NEGATIVE_X,
	POSITIVE_X,
	NEGATIVE_Y,
	POSITIVE_Y,
	NEGATIVE_Z,
	POSITIVE_Z,
};

class Column
{
public:
	explicit Column(glm::dvec3 pos, float size = 1);
	void Draw() const;

private:
	float m_size;

	glm::dvec3 m_pos;
};