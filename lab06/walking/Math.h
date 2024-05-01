#pragma once
#include <cmath>
#include <algorithm>

inline bool IsEqual(double x, double y)
{
	const double epsilon = 1e-6;
	return std::abs(x - y) <= epsilon * std::abs(x);
}

inline double Normalize(double x)
{
	return std::clamp(x, 0.0, 1.0);
}
