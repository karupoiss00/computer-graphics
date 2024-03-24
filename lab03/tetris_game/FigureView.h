#pragma once
#include <memory>
#include "IDrawable.h"
#include "CellView.h"
#include "Vec.h"
#include "Figure.h"

class FigureView : public IDrawable
{
public:
	FigureView(std::shared_ptr<Figure> figure)
		: m_figure(figure)
	{}

	void Draw() 
	{
		auto data = m_figure->GetData();
		Vec2d pos = m_figure->GetPosition();
		for (unsigned y = 0; y < data.size(); y++)
		{
			for (unsigned x = 0; x < data[y].size(); x++)
			{
				if (data[y][x].filled)
				{
					Vec2d cellPos = Vec2d{ double(x) + pos.x, double(y) + pos.y };
					CellView cell(data[y][x], cellPos);
					cell.Draw();
				}
			}
		}
	}
private:
	std::shared_ptr<Figure> m_figure;
};