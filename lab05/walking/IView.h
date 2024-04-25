#pragma once

class IView
{
public:
	virtual void Setup() = 0;
	virtual void Update(double dt) = 0;
	virtual void Draw() = 0;
	virtual void DrawUI() = 0;

	virtual void OnKeyDown(int key, int scancode, int mods) = 0;
	virtual void OnKeyUp(int key, int scancode, int mods) = 0;
	virtual void OnMouseMove(double x, double y) = 0;
	virtual void OnResize(int width, int height) = 0;
};