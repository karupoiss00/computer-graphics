#pragma once
#include "Vec.h"
#include "FigureData.h"
#include "FigureType.h"

class Figure
{
public:
	Figure(FigureType type, Vec2d position, Color3d color = {1, 0, 0});

	void SetPosition(Vec2d pos);
	void Rotate();

	Vec2d GetPosition();
	FigureData GetData();
private:
	Vec2d m_position;
	FigureData m_data;
};