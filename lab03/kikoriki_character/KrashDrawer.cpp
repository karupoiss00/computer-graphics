#define _USE_MATH_DEFINES
#include <cmath>
#include <gl/glut.h>
#include "KrashDrawer.h"
#include "Drawer.h"

using namespace std;

void DrawBezierPolygon(vector<std::array<double, 3>> points, double dx, double dy)
{
	for (auto& point : points)
	{
		point[0] = point[0] + dx;
		point[1] = point[1] + dy;
	}

	DrawBezierPolygon(points, true);
}

void DrawLeftEar(double dx, double dy)
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

	DrawBezierPolygon(points, dx, dy);
}

void DrawRightEar(double dx, double dy)
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

	DrawBezierPolygon(points, dx, dy);
}

void DrawRightLeg(double dx, double dy)
{
	vector<std::array<double, 3>> points = {
		{1.0, -4.9, 0.0},
		{3.0, -4.9, 0.0},
		{4.0, -5.9, 0.0},
		{4.0, -6.4, 0.0},
		{3.5, -6.9, 0.0},
		{2.5, -6.9, 0.0},
		{1.5, -6.9, 0.0},
		{0.0, -6.9, 0.0},
		{0.5, -5.9, 0.0},
		{0.5, -4.9, 0.0},
	};

	DrawBezierPolygon(points, dx, dy);
}

void DrawLeftLeg(double dx, double dy)
{
	vector<std::array<double, 3>> points = {
		{-1.0, -4.9, 0.0},
		{-3.0, -4.9, 0.0},
		{-4.0, -5.9, 0.0},
		{-4.0, -6.4, 0.0},
		{-3.5, -6.9, 0.0},
		{-2.5, -6.9, 0.0},
		{-1.5, -6.9, 0.0},
		{-0.0, -6.9, 0.0},
		{-0.5, -5.9, 0.0},
		{-0.5, -4.9, 0.0},
	};

	DrawBezierPolygon(points, dx, dy);
}

void DrawRightArm(double dx, double dy)
{
	vector<std::array<double, 3>> points = {
		{4.5, -1.5, 0.0},
		{4.5, -1.0, 0.0},
		{5.0, -1.1, 0.0},
		{6.0, -2.0, 0.0},
		{6.0, -3.5, 0.0},
		{6.5, -5.0, 0.0},
		{5.0, -5.0, 0.0},
		{4.0, -5.0, 0.0},
		{3.0, -4.0, 0.0},
		{5.0, -2.5, 0.0},
	};

	DrawBezierPolygon(points, dx, dy);
}

void DrawLeftArm(double dx, double dy)
{
	vector<std::array<double, 3>> points = {
		{-4.5, -1.5, 0.0},
		{-4.5, -1.0, 0.0},
		{-5.0, -1.1, 0.0},
		{-6.0, -2.0, 0.0},
		{-6.0, -3.5, 0.0},
		{-6.5, -5.0, 0.0},
		{-5.0, -5.0, 0.0},
		{-4.0, -5.0, 0.0},
		{-3.0, -4.0, 0.0},
		{-5.0, -2.5, 0.0},
	};

	DrawBezierPolygon(points, dx, dy);
}

void DrawBody(double dx, double dy)
{
	glColor3d(0.36, 0.75, 0.85);
	DrawFilledEllipse(dx, dy, 5, 5);
}

void DrawEars(double dx, double dy)
{
	glColor3d(0.36, 0.75, 0.85);
	DrawLeftEar(dx + -2.1, dy + 4);
	DrawRightEar(dx + 0.85, dy + 4);
}

void DrawLegs(double dx, double dy)
{
	glColor3d(0.36, 0.75, 0.85);
	DrawRightLeg(dx, dy);
	DrawLeftLeg(dx, dy);
}

void DrawArms(double dx, double dy)
{
	glColor3d(0.36, 0.75, 0.85);
	DrawRightArm(dx, dy);
	DrawLeftArm(dx, dy);
}


void DrawKrash(double dx, double dy)
{
	DrawBody(dx, dy);
	DrawEars(dx, dy);
	DrawArms(dx, dy);
	DrawLegs(dx, dy);
}