#pragma once
#include <array>
#include "CellData.h"

constexpr size_t FIELD_WIDTH = 10;
constexpr size_t FIELD_HEIGHT = 20;

using FieldData = std::array<
	std::array<CellData, FIELD_WIDTH>, 
	FIELD_HEIGHT
>;