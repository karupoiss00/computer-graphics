#pragma once
#include <random>

struct Color3d
{
	double r, g, b;
};

inline Color3d GenerateRandomColor3d()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> dis(0, 1);

	return { dis(gen), dis(gen), dis(gen) };
}