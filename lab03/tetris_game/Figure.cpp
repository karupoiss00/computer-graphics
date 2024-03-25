#include "Figure.h"
#include "Rotate.h"

Figure::Figure(FigureType type, Vec2d position, Color3d color)
	: m_data(CreateFigureData(type, color))
	, m_position(position)
{

}
void Figure::Rotate()
{
	m_data = RotateMatrix(m_data);
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