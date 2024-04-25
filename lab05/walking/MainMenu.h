#pragma once
#include <functional>
#include "IScreenProvider.h"
#include "IView.h"

class MainMenu : public IView
{
public:
	MainMenu(
		IScreenProvider const& screenProvider,
		std::function<void()> onGameStart
	);

	void Setup() {};
	void Update(double dt) {};
	void Draw() {};
	void DrawUI();

	void OnKeyDown(int key, int scancode, int mods) {};
	void OnKeyUp(int key, int scancode, int mods) {};
	void OnMouseMove(double x, double y) {};
	void OnResize(int width, int height) {};
private:
	std::function<void()> m_onGameStartFn;
	IScreenProvider const& m_screenProvider;
};