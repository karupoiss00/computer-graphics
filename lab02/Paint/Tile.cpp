#include "Tile.h"

Tile::Tile(Color color) noexcept
	: m_pixels()
{
	for (auto& row : m_pixels)
	{
		std::fill_n(row.begin(), row.size(), color);
	}

	assert(m_instanceCount >= 0);
	++m_instanceCount;
}

Tile::Tile(const Tile& other)
	: m_pixels(other.m_pixels)
{
	assert(m_instanceCount >= 0);
	++m_instanceCount;
}

Tile::~Tile()
{
	--m_instanceCount;
	assert(m_instanceCount >= 0);
}

void Tile::SetPixel(Point p, Color color) noexcept
{
	if (!IsValidPoint(p))
	{
		return;
	}

	m_pixels[p.y][p.x] = color;
}

Color Tile::GetPixel(Point p) const noexcept
{
	if (!IsValidPoint(p))
	{
		return 0x000000;
	}

	return m_pixels[p.y][p.x];
}

int Tile::GetInstanceCount() noexcept
{
	return m_instanceCount;
}

bool Tile::IsValidPoint(Point const& p) const
{
	return p.x >= 0 && p.x < SIZE
		&& p.y >= 0 && p.y < SIZE;
}