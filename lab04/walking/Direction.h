#pragma once
#include <vector>

enum class Direction
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
};

const std::vector<Direction> DIRECTIONS = {
	Direction::FORWARD,
	Direction::BACKWARD,
	Direction::LEFT,
	Direction::RIGHT
};