#pragma once
#include "Color.h"

class Pixel
{
public:
	Color GetColor() const&
	{
		return m_color;
	}
	void SetColor(Color color)
	{
		m_color = color;
	};

private:
	Color m_color;
};