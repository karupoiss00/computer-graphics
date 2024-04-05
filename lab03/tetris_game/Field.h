#pragma once
#include "Vec.h"
#include "FieldData.h"
#include "FigureData.h"

class Field
{
public:
	void PutFigure(Vec2d point, FigureData figure);
	// константные методы
	unsigned GetWidth();
	unsigned GetHeight();
	bool CanPutFigure(Vec2d point, FigureData figure);
	FieldData GetData();
	[[nodicard]] unsigned Update();
	void Clear();
protected:
	// сделать приватными
	void RemoveEmptyLines();
	unsigned RemoveFilledLines();
private:
	FieldData m_data;
};