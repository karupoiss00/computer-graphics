#define _USE_MATH_DEFINES
#include <cmath>
#include <functional>
#include <gl/glut.h>
#include "KrashDrawer.h"
#include "Drawer.h"

using namespace std;
using MathFn = std::function<double(double)>;

void DrawBody();
void DrawFace();
void DrawEars();
void DrawArms();
void DrawLegs();

// [solved] сделать смещение через матрицы

void DrawKrash()
{
	DrawBody();
	DrawFace();
	DrawEars();
	DrawArms();
	DrawLegs();
}

void DrawGraph(MathFn fn, double minX, double maxX)
{
	glBegin(GL_POLYGON);

	for (double x = minX; x < maxX; x += 0.1)
	{
		glVertex2d(x, fn(x));
	}

	glVertex2d(maxX, fn(maxX));

	glEnd();
}

void DrawLeftEar()
{
	vector<std::array<double, 3>> points = {
		{-2.0, 4.0, 0.0},
		{-2.0, 7.0, 0.0},
		{-2.5, 11.5, 0.0},
		{-5, 13.75, 0.0},
		{-5, 16.0, 0.0},
		{-3.5, 17.5, 0.0},
		{1.0, 14.5, 0.0},
		{-0.5, 17.5, 0.0},
		{1.0, 8.5, 0.0},
		{-1.0, 4.0, 0.0},
	};

	DrawBezierPolygon(points, true);
}

void DrawRightEar()
{
	vector<std::array<double, 3>> points = {
		{1.0, 4.0, 0.0},
		{-0.32, 9.61, 0.0},
		{-0.98, 15.88, 0.0},
		{2.32, 15.44, 0.0},
		{8.81, 13.46, 0.0},
		{1.0, 9.61, 0.0},
		{2.32, 4.0, 0.0},
	};

	DrawBezierPolygon(points, true);
}

void DrawRightLeg()
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

	DrawBezierPolygon(points, true);
}

void DrawLeftLeg()
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

	DrawBezierPolygon(points, true);
}

void DrawRightArm()
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

	DrawBezierPolygon(points, true);
}

void DrawLeftArm()
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

	DrawBezierPolygon(points, true);
}

void DrawBody()
{
	glColor3d(0.36, 0.75, 0.85);
	DrawFilledEllipse(0, 0, 5, 5);
}

void DrawEars()
{
	glColor3d(0.36, 0.75, 0.85);
	DrawLeftEar();
	DrawRightEar();
}

void DrawLegs()
{
	glColor3d(0.36, 0.75, 0.85);
	DrawRightLeg();
	DrawLeftLeg();
}

void DrawArms()
{
	glColor3d(0.36, 0.75, 0.85);
	DrawRightArm();
	DrawLeftArm();
}

void DrawPupil(double dx, double dy)
{
	glColor3d(0, 0, 0);
	DrawFilledEllipse(dx, dy, 0.35, 0.5);
	glColor3d(1, 1, 1);
	DrawFilledEllipse(0.3, 0.2, 0.1, 0.1);
}

void DrawLeftEye()
{
	glColor3d(1, 1, 1);
	DrawFilledEllipse((-1.2), 1, 1, 1.2);
	DrawPupil((-0.55), 1);
}

void DrawRightEye()
{
	glColor3d(1, 1, 1);
	DrawFilledEllipse(1, 1.2, 1.1, 1.5);
	DrawPupil(0.35, 1);
}

void DrawMouth()
{
	glColor3d(0.06, 0.42, 0.62);

	vector<std::array<double, 3>> points = {
		{-2.5, -0.3, 0.0},
		{0.0, -2.3, 0.0},
		{2.5, -0.3, 0.0},
	};

	DrawBezierPolygon(points, false);

	for (auto& p : points)
	{
		p[1] += 0.01;
	}

	DrawBezierPolygon(points, false);

	for (auto& p : points)
	{
		p[1] += 0.01;
	}

	DrawBezierPolygon(points, false);
}

void DrawNose()
{
	glColor3d(0.91, 0.41, 0.44);
	DrawFilledEllipse(-0.15, 0, 0.5, 0.5);
}

void DrawLeftEyeBrow()
{
	glColor3d(0.06, 0.42, 0.62);
		
	vector<std::array<double, 3>> points = {
		{-0.7, 3.2, 0.0},
		{-1.3, 3.2, 0.0},
		{-1.8, 2.0, 0.0},
		{-2.4, 2.7, 0.0},
		{-1.5, 3.6, 0.0},
		{-0.7, 3.7, 0.0},
	};
	DrawBezierPolygon(points, true);
}

void DrawRightEyeBrow()
{
	glColor3d(0.06, 0.42, 0.62);

	vector<std::array<double, 3>> points = {
		{0.2, 3.2, 0.0},
		{1.0, 3.5, 0.0},
		{2.3, 2.5, 0.0},
		{2.3, 3.7, 0.0},
		{0.2, 3.7, 0.0},
	};
	DrawBezierPolygon(points, true);
}

void DrawTeeth()
{
	glColor3d(0.06, 0.42, 0.62);
	DrawGraph([](double x) {
		return 2.7 * pow((x + 0.5), 2) - 2.2;
	}, -1.15, 0.1);
	DrawGraph([](double x) {
		return 2 * pow((x - 0.2), 2) - 2.0;
	}, -0.35, 0.85);

	glColor3d(1.0, 1.0, 1.0);
	DrawGraph([](double x) {
		return 2.7 * pow((x + 0.5), 2) - 2.1;
	}, -1.1, 0.05);
	DrawGraph([](double x) {
		return 2 * pow((x - 0.2), 2) - 1.9;
	}, -0.3, 0.8);

	glColor3d(0.06, 0.42, 0.62);
	glBegin(GL_LINES);
	glVertex2d(-0.1, -1.3);
	glVertex2d(-0.1, -1.8);
	glEnd();
}


void DrawFace()
{
	DrawLeftEye();
	DrawRightEye();
	DrawLeftEyeBrow();
	DrawRightEyeBrow();
	DrawNose();
	DrawTeeth();
	DrawMouth();
}
