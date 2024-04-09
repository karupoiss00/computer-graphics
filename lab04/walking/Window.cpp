#include <iostream>
#include "FrequencyTimer.h"
#include "pch.h"
#include "Window.h"

Window::Window(int w, int h, const char* title)
	: BaseWindow(w, h, title)
	, m_light({ 0.0f, 8.0f, 0.0f })
	, m_camera()
	, m_cameraController(m_camera)
	, m_renderConfigEditor(m_renderConfig)
	, m_world()
	, m_worldRenderer(m_world)
	, m_player()
	, m_playerController(m_player, m_camera)
{}

void Window::SetupLight()
{
	m_light.SetDiffuseIntensity({ 0.3f, 0.6f, 0.3f, 1.0f });
	m_light.SetAmbientIntensity({ 0.3f, 0.3f, 0.3f, 1.0f });
	m_light.SetSpecularIntensity({ 0.3f, 0.3f, 0.3f, 1.0f });
}

void Window::OnKeyDown(int key, int scancode, int mods)
{
	if (key == GLFW_KEY_ESCAPE)
	{
		m_showRenderConfig = !m_showRenderConfig;
	}

	if (key == GLFW_KEY_W)
	{
		m_playerController.SetSpeed(Direction::FORWARD, 2);
	}
	if (key == GLFW_KEY_S)
	{
		m_playerController.SetSpeed(Direction::BACKWARD, 2);
	}
	if (key == GLFW_KEY_A)
	{
		m_playerController.SetSpeed(Direction::LEFT, 2);
	}
	if (key == GLFW_KEY_D)
	{
		m_playerController.SetSpeed(Direction::RIGHT, 2);
	}
}

void Window::OnKeyUp(int key, int scancode, int mods)
{
	if (key == GLFW_KEY_W)
	{
		m_playerController.SetSpeed(Direction::FORWARD, 0);
	}
	if (key == GLFW_KEY_S)
	{
		m_playerController.SetSpeed(Direction::BACKWARD, 0);
	}
	if (key == GLFW_KEY_A)
	{
		m_playerController.SetSpeed(Direction::LEFT, 0);
	}
	if (key == GLFW_KEY_D)
	{
		m_playerController.SetSpeed(Direction::RIGHT, 0);
	}
}

void Window::OnMouseMove(double x, double y)
{
	m_cameraController.MouseMoveHandler(
		GetFramebufferSize(),
		x,
		y,
		MouseMovePrevented()
	);
}

void Window::OnResize(int width, int height)
{
	ApplyProjectionChanges(width, height);
}

void Window::OnRunStart()
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);

	m_light.Apply(GL_LIGHT0);
}

void Window::Draw(int width, int height)
{
	ApplyChanges();

	auto clearColor = m_renderConfig.m_backgroundColor;
	auto cameraMatrix = m_camera.GetWorldToViewMatrix();

	glClearColor(
		clearColor[0],
		clearColor[1],
		clearColor[2],
		clearColor[3]
	);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	ShowCursor(m_showRenderConfig);
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(&cameraMatrix[0][0]);

	m_worldRenderer.Render();
}


void Window::DrawGUI(int width, int height)
{
	ImGui::NewFrame();
	m_renderConfigEditor.Render(m_showRenderConfig);
	m_renderStats.Render(m_renderConfig.m_showStats);
	ImGui::Render();
}

bool Window::MouseMovePrevented()
{
	return m_showRenderConfig;
}

void Window::ApplyChanges()
{
	auto deltaTime = GetEllapsedTime();
	m_playerController.Update(deltaTime);

	auto size = GetFramebufferSize();
	ApplyProjectionChanges(int(size.x), int(size.y));
}

void Window::ApplyProjectionChanges(int width, int height)
{
	float aspect = float(width) / float(height);
	float fov = m_renderConfig.m_fov * float(M_PI) / 180.0f;
	auto projectionMatrix = glm::perspective(fov, aspect, m_renderConfig.m_zNear, m_renderConfig.m_zFar);

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(&projectionMatrix[0][0]);
	glMatrixMode(GL_MODELVIEW);
}