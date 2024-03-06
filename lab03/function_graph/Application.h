#pragma once
#include "GLApplication.h"

class CMyApplication : public CGLApplication
{
public:
	CMyApplication(const char* title);
	~CMyApplication(void);

protected:
	virtual void OnInit();
	virtual void OnDisplay(void);
	virtual void OnReshape(int width, int height);

public:
	static void FillEllipse(float xCenter, float yCenter, float rx, float ry, int points = 360);
};