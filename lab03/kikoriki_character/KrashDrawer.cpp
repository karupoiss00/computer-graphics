#define _USE_MATH_DEFINES
#include <cmath>
#include <gl/glut.h>
#include "KrashDrawer.h"
#include "Drawer.h"

using namespace std;

void DrawLeftEar(double dx, double dy, double scale = 1)
{
	vector<std::array<double, 3>> points = {
		{0.0, 0.0, 0.0},
		{0.0, 3.0, 0.0},
		{-0.5, 7.5, 0.0},
		{-3, 9.75, 0.0},
		{-3, 12.0, 0.0},
		{-1.5, 13.5, 0.0},
		{3.0, 10.5, 0.0},
		{1.5, 13.5, 0.0},
		{3.0, 4.5, 0.0},
		{1.0, 0.0, 0.0},
	};

	for (auto& point : points)
	{
		point[0] = point[0] * scale + dx;
		point[1] = point[1] * scale + dy;
	}

	glColor3d(0.36, 0.75, 0.85);
	DrawBezierPolygon(points, true);
}

void DrawRightEar(double dx, double dy, double scale = 1)
{
	vector<std::array<double, 3>> points = {
		{0.0, 0.0, 0.0},
		{-1.32, 5.61, 0.0},
		{-1.98, 11.88, 0.0},
		{1.32, 11.44, 0.0},
		{7.81, 9.46, 0.0},
		{0.0, 5.61, 0.0},
		{1.32, 0.0, 0.0},
	};

	for (auto& point : points)
	{
		point[0] = point[0] * scale + dx;
		point[1] = point[1] * scale + dy;
	}

	glColor3d(0.36, 0.75, 0.85);
	DrawBezierPolygon(points, true);
}


void DrawBody()
{
	glColor3d(0.36, 0.75, 0.85);
	DrawFilledEllipse(0, 0, 5, 5);
}

void DrawKrash()
{
	DrawBody();
	DrawLeftEar(-2.1, 4);
	DrawRightEar(0.85, 4);
}