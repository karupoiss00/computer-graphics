#pragma once
#include <vector>

template<typename T>
std::vector<std::vector<T>> RotateMatrix(std::vector<std::vector<T>> const& v)
{
	if (v.size() == 0 || (v[0].size() != v.size()))
	{
		throw std::exception("matrix must be square");
	}

	auto rotatedCopy = v;

	const auto N = v.size() - 1;

	for (unsigned y = 0; y < v.size(); y++)
	{
		for (unsigned x = 0; x < v[y].size(); x++)
		{
			rotatedCopy[y][x] = v[N - x][y];
		}
	}

	return rotatedCopy;
}