#pragma once
#include <map>
#include <string>
#include <functional>
#include "Game.h"
#include "MainMenu.h"
#include "BaseWindow.h"
#include "IScreenProvider.h"

class Window : public BaseWindow, public IScreenProvider
{
public:
	Window(int w, int h, const char* title);

	glm::ivec2 GetScreenSize() const override;
	void SetCursorVisible(bool visible) const override;
private:
	void OnRunStart() override;

	void OnKeyDown(int key, int scancode, int mods) override;

	void OnKeyUp(int key, int scancode, int mods) override;

	void OnMouseMove(double x, double y) override;

	void OnResize(int width, int height) override;

	void Update(double dt) override;

	void Draw(int width, int height) override;
	
	void DrawGUI(int width, int height) override;

	void SwitchView(IView* view);

	Game m_game;
	MainMenu m_menu;

	IView* m_currentView;
};