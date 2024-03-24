#pragma once
#include <memory>
#include "IDrawable.h"
#include "CellView.h"
#include "Vec.h"
#include "Field.h"

class FieldView : public IDrawable
{
public:
	FieldView(std::shared_ptr<Field> field, Vec2d position)
		: m_field(field), m_pos(position)
	{}

	void Draw()
	{
		auto data = m_field->GetData();
		for (unsigned y = 0; y < data.size(); y++)
		{
			for (unsigned x = 0; x < data[y].size(); x++)
			{
				CellView cell(data[y][x], Vec2d{ double(x), double(y) });
				cell.Draw();
			}
		}
	}
private:
	Vec2d m_pos;
	std::shared_ptr<Field> m_field;
};