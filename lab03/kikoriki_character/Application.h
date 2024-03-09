#pragma once
#include <functional>
#include "GLApplication.h"

using MathFn = std::function<double(double)>;

class CApplication : public CGLApplication
{
public:
	CApplication(const char* title);
	~CApplication(void);

protected:
	virtual void OnInit();
	virtual void OnDisplay(void);
	virtual void OnReshape(int width, int height);

public:
	static void DrawCoordinatesSystem(float step);
	static void DrawGrid(float cellSize);
};