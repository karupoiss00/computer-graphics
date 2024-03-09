#pragma once
#include <vector>
#include <array>

void DrawFilledEllipse(double x, double y, double rx, double ry);
void DrawBezierPolygon(std::vector<std::array<double, 3>> points, bool fill = false, bool drawPoints = false);