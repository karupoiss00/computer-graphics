#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include "Application.h"
#include "Drawer.h"
#include "KrashDrawer.h"

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 800;

constexpr double MAX_X = 20;
constexpr double MIN_X = -MAX_X;
constexpr double MAX_Y = 20;
constexpr double MIN_Y = -MAX_Y;

CApplication::CApplication(const char* title)
	: CGLApplication(title, WINDOW_WIDTH, WINDOW_HEIGHT)
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
	DrawKrash();
}

void CApplication::OnReshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	GLfloat heightWidthRatio = width <= height 
		? static_cast<GLfloat>(height) / static_cast<GLfloat>(width)
		: 1;
	GLfloat widthHeightRatio = width > height 
		? static_cast<GLfloat>(width) / static_cast<GLfloat>(height)
		: 1;

	gluOrtho2D(
		MIN_X * widthHeightRatio,
		MAX_X * widthHeightRatio,
		MIN_Y * heightWidthRatio,
		MAX_Y * heightWidthRatio
	);
}