#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <functional>
#include "Application.h"

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 800;

constexpr double MAX_X = 20;
constexpr double MAX_Y = 20;

CApplication::CApplication(const char* title)
	: CGLApplication(title, WINDOW_WIDTH, WINDOW_HEIGHT)
	, m_game()
	, m_figureView(m_game.GetFigure())
	, m_fieldView(m_game.GetField(), { 0, 0 })
{
	m_prevTimePoint = std::chrono::system_clock::now();
}


CApplication::~CApplication(void)
{
}

void CApplication::OnIdle()
{
	auto delay = m_game.GetUpdateDelay();
	auto currentTime = std::chrono::system_clock::now();
	auto ellapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - m_prevTimePoint).count();
	if (ellapsedTime >= delay)
	{
		m_game.Update();
		m_prevTimePoint = std::chrono::system_clock::now();
		PostRedisplay();
	}
}


void CApplication::OnKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
		m_game.RotateFigure();
		break;
	case 'a':
		m_game.MoveFigureLeft();
		break;
	case 's':
		m_game.MoveFigureDown();
		break;
	case 'd':
		m_game.MoveFigureRight();
		break;
	case 'p':
		m_game.SetPaused(!m_game.IsPaused());
		break;
	}
	
	PostRedisplay();
}

void CApplication::OnInit()
{
	glClearColor(1, 1, 1, 1);
}

void CApplication::OnDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_fieldView.Draw();
	m_figureView.Draw();
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
		0,
		MAX_X * widthHeightRatio,
		MAX_Y * heightWidthRatio,
		0
	);
}