#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include "Application.h"

constexpr double MAX_X = 20;
constexpr double MIN_X = -MAX_X;
constexpr double MAX_Y = 20;
constexpr double MIN_Y = -MAX_Y;

CApplication::CApplication(const char* title)
	: CGLApplication(title, 800, 800)
{

}	

CApplication::~CApplication(void)
{
}

void CApplication::OnInit()
{
	glClearColor(1, 1, 1, 1);
}

void CApplication::OnDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	DrawGrid(1);
	DrawCoordinatesSystem(1);
	DrawGraph(
		[](double x) -> double {
			return 2 * pow(x, 2) - 3 * x - 8;
		}, -3, 2
	);
}

void CApplication::OnReshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	GLfloat heightWidthRatio = width <= height 
		? (GLfloat)height / (GLfloat)width 
		: 1;
	GLfloat widthHeightRatio = width > height 
		? (GLfloat)width / (GLfloat)height
		: 1;

	gluOrtho2D(
		MIN_X * widthHeightRatio,
		MAX_X * widthHeightRatio,
		MIN_Y * heightWidthRatio,
		MAX_Y * heightWidthRatio
	);
}

void CApplication::DrawGraph(MathFn fn, float minX, float maxX)
{
	glBegin(GL_LINE_STRIP);

	glColor3f(1, 0, 0);

	for (double x = minX; x < maxX; x += 0.1)
	{
		glVertex2d(x, fn(x));
	}

	glVertex2d(maxX, fn(maxX));

	glEnd();
}

void CApplication::DrawCoordinatesSystem(float step)
{
	glBegin(GL_LINES);

	glColor3f(0, 0, 0);

	//ось Y
	glVertex2d(0, MIN_Y);
	glVertex2d(0, MAX_Y);

	//стрелка для Y
	glVertex2d(-0.125f, MAX_Y - 0.3f);
	glVertex2d(0, MAX_Y);
	glVertex2d(0, MAX_Y);
	glVertex2d(0.125f, MAX_Y - 0.3f);

	// деления для Y
	for (double y = MIN_Y; y < MAX_Y; y += step)
	{
		glVertex2d(-0.1f, y);
		glVertex2d(0.1f, y);
	}

	//ось X
	glVertex2d(MIN_X, 0);
	glVertex2d(MAX_X, 0);

	//стрелка для X
	glVertex2d(MAX_X - 0.3f , -0.125f);
	glVertex2d(MAX_X, 0);
	glVertex2d(MAX_X, 0);
	glVertex2d(MAX_X - 0.3f, 0.125f);

	// деления для X
	for (double x = MIN_X; x < MAX_X; x += step)
	{
		glVertex2d(x, -0.1f);
		glVertex2d(x, 0.1f);
	}

	glEnd();
}

void CApplication::DrawGrid(float cellSize)
{
	glBegin(GL_LINES);

	glColor3f(0.9f, 0.9f, 0.9f);

	// разлиновка X
	for (double x = MIN_X; x < MAX_X; x += cellSize)
	{
		glVertex2d(x, MIN_Y);
		glVertex2d(x, MAX_Y);
	}

	// разлиновка Y
	for (double y = MIN_X; y < MAX_X; y += cellSize)
	{
		glVertex2d(MIN_X, y);
		glVertex2d(MAX_X, y);
	}

	glEnd();
}