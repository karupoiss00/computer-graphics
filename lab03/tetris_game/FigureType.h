#pragma once
#include <stdexcept>
#include "FigureData.h"

enum class FigureType
{
	L,
	J,
	O,
	I,
	S,
	Z,
	A
};

FigureData CreateFigureData(FigureType type, Color3d color);
FigureType GetRandomFigureType();