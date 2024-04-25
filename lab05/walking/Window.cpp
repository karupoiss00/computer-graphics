#include <iostream>
#include "pch.h"
#include "Window.h"

Window::Window(int w, int h, const char* title)
	: BaseWindow(w, h, title)
	, m_game(*this, [this]() { SwitchView(&m_menu); })
	, m_menu(*this, [this]() { SwitchView(&m_game); })
	, m_currentView(&m_menu)
{
}

void Window::OnKeyDown(int key, int scancode, int mods)
{
	m_currentView->OnKeyDown(key, scancode, mods);
}

void Window::OnKeyUp(int key, int scancode, int mods)
{
	m_currentView->OnKeyUp(key, scancode, mods);
}

void Window::OnMouseMove(double x, double y)
{
	m_currentView->OnMouseMove(x, y);
}

void Window::OnResize(int width, int height)
{
	m_currentView->OnResize(width, height);
}

void Window::Update(double dt)
{
	m_currentView->Update(dt);
}

void Window::Draw(int width, int height)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_currentView->Draw();
}

void Window::DrawGUI(int width, int height)
{
	ImGui::NewFrame();
	m_currentView->DrawUI();
	ImGui::Render();
}

glm::ivec2 Window::GetScreenSize() const
{
	return GetFramebufferSize();
}


void Window::SetCursorVisible(bool visible) const
{
	this->ShowCursor(visible);
}

void Window::SwitchView(IView* view)
{
	m_currentView = view;
	m_currentView->Setup();
}