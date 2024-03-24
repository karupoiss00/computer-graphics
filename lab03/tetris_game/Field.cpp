#include "Field.h"

bool Field::CanPutFigure(Vec2d point, FigureData figure)
{
	for (unsigned y = 0; y < figure.size(); y++)
	{
		for (unsigned x = 0; x < figure[y].size(); x++)
		{
			if (figure[y][x].filled && (
				point.x + x < 0 ||
				point.x + x >= GetWidth() ||
				point.y + y < 0 ||
				point.y + y >= GetHeight() ||
				m_data[point.y + y][point.x + x].filled
			)) 
			{
				return false;
			}
		}
	}

	return true;
}

void Field::PutFigure(Vec2d point, FigureData figure)
{
	if (!CanPutFigure(point, figure))
	{
		return;
	}

	for (unsigned y = 0; y < figure.size(); y++)
	{
		for (unsigned x = 0; x < figure[y].size(); x++)
		{
			if (figure[y][x].filled)
			{
				m_data[point.y + y][point.x + x] = figure[y][x];
			}
		}
	}
}

unsigned Field::Update()
{
	unsigned reachedLines = RemoveFilledLines();
	RemoveEmptyLines();
	return reachedLines;
}

void Field::RemoveEmptyLines()
{
	FieldData updatedField;
	unsigned realY = m_data.size() - 1;

	for (unsigned y = m_data.size() - 1; y > 0; y--)
	{
		bool lineEmpty = true;
		for (unsigned x = 0; x < m_data[y].size(); x++)
		{
			lineEmpty = lineEmpty && !m_data[y][x].filled;
		}

		if (lineEmpty)
		{
			continue;
		}

		for (unsigned x = 0; x < m_data[y].size(); x++)
		{
			updatedField[realY][x] = m_data[y][x];
		}
		realY--;
	}

	m_data = updatedField;
}

unsigned Field::RemoveFilledLines()
{
	unsigned removedLines = 0;
	for (auto& line : m_data)
	{
		bool lineFilled = true;

		for (auto const& cell : line)
		{
			lineFilled = lineFilled && cell.filled;
		}

		if (!lineFilled)
		{
			continue;
		}
		removedLines++;
		for (auto& cell : line)
		{
			cell.Clear();
		}
	}

	return removedLines;
}

unsigned Field::GetWidth()
{
	return m_data[0].size();
}

unsigned Field::GetHeight()
{
	return m_data.size();
}

void Field::Clear()
{
	for (auto& line : m_data)
	{
		for (auto& cell : line)
		{
			cell.Clear();
		}
	}
}

FieldData Field::GetData()
{
	return m_data;
}