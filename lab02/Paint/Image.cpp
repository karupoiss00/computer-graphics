#include <cassert>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <vector>

#include "Image.h"

using namespace std;

constexpr Size DEFAULT_SIZE = { 800, 800 };

Image::Image(Size size, Color color)
	: m_size(move(size))
{
	Fill(color);
}

Image::Image(std::vector<std::vector<Color>> imageColors)
	: Image(
		Size(
			imageColors.size() > 0 
				? imageColors[0].size() 
				: 0, 
			imageColors.size()
		)
	)
{
	auto width = imageColors.size() > 0
		? imageColors[0].size()
		: 0;
	auto height = imageColors.size();

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			SetPixel({ x, y }, imageColors[y][x]);
		}
	}
}

Image::Image()
	: Image(DEFAULT_SIZE)
{}

Size Image::GetSize() const noexcept
{
	return m_size;
}

Color Image::GetPixel(Point p) const noexcept
{
	try 
	{
		auto tile = GetTile(p);
		int relativeX = p.x % Tile::SIZE;
		int relativeY = p.y % Tile::SIZE;

		return tile->GetPixel({ relativeX, relativeY });
	}
	catch (...)
	{}

	return ' ';
}

void Image::SetPixel(Point p, Color color)
{
	try
	{
		auto& tile = GetTile(p);
		int relativeX = p.x % Tile::SIZE;
		int relativeY = p.y % Tile::SIZE;

		tile--->SetPixel({ relativeX, relativeY }, color);
	}
	catch (...) {}
}

void Image::Fill(Color color)
{
	size_t tilesHorizontalCount = m_size.width / Tile::SIZE + (m_size.width % Tile::SIZE != 0);
	size_t tilesVerticalCount = m_size.height / Tile::SIZE + (m_size.height % Tile::SIZE != 0);

	CoW<Tile> filledTile(color);

	m_tiles = vector<vector<CoW<Tile>>>(
		tilesVerticalCount,
		vector<CoW<Tile>>(tilesHorizontalCount, filledTile));
}

CoW<Tile>& Image::GetTile(Point const& p)
{
	if (p.x < 0 || p.x >= m_size.width || p.y < 0 || p.y >= m_size.height)
	{
		throw std::out_of_range("tile y out of range");
	}

	unsigned tileX = static_cast<unsigned>(p.x / Tile::SIZE);
	unsigned tileY = static_cast<unsigned>(p.y / Tile::SIZE);

	return m_tiles[tileY][tileX];
}

CoW<Tile> const& Image::GetTile(Point const& p) const
{
	if (p.x < 0 || p.x >= m_size.width || p.y < 0 || p.y >= m_size.height)
	{
		throw std::out_of_range("tile y out of range");
	}

	unsigned tileX = static_cast<unsigned>(p.x / Tile::SIZE);
	unsigned tileY = static_cast<unsigned>(p.y / Tile::SIZE);

	return m_tiles[tileY][tileX];
}
