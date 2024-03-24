#pragma once
#include <functional>
#include <memory>
#include <chrono>
#include "GLApplication.h"
#include "FigureView.h"
#include "FieldView.h"
#include "TetrisGame.h"

using MathFn = std::function<double(double)>;

class CApplication : public CGLApplication
{
public:
	CApplication(const char* title);
	~CApplication(void);

protected:
	virtual void OnInit();
	virtual void OnIdle();
	virtual void OnDisplay(void);
	virtual void OnReshape(int width, int height);
	virtual void OnKeyboard(unsigned char key, int x, int y);
private:
	std::chrono::time_point<std::chrono::system_clock> m_prevTimePoint;
	TetrisGame m_game;
	FieldView m_fieldView;
	FigureView m_figureView;
};