#include "Figure.h"

Figure::Figure(FigureType type, Vec2d position, Color3d color)
	: m_data(CreateFigureData(type, color))
	, m_position(position)
{

}
void Figure::Rotate()
{
	if (m_data.size() == 0 || (m_data[0].size() != m_data.size()))
	{
		throw std::exception("figure matrix must be square");
	}

	auto initialData = m_data;

	const auto N = m_data.size() - 1;

	for (unsigned y = 0; y < m_data.size(); y++)
	{
		for (unsigned x = 0; x < m_data[y].size(); x++)
		{
			m_data[y][x] = initialData[N - x][y];
		}
	}
}

void Figure::SetPosition(Vec2d pos)
{
	m_position = pos;
}

Vec2d Figure::GetPosition()
{
	return m_position;
}

FigureData Figure::GetData()
{
	return m_data;
}