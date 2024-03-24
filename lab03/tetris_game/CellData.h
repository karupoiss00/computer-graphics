#pragma once
#include "Color.h"

struct CellData
{
	CellData()
		: color({ 0, 0, 0 }), filled(false)
	{}

	CellData(Color3d _color, bool _filled)
		: color(_color), filled(_filled)
	{}

	void Clear()
	{
		filled = false;
		color = { 0, 0, 0 };
	}

	Color3d color;
	bool filled;
};