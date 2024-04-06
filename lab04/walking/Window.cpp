#include <iostream>
#include "pch.h"
#include "Window.h"

Window::Window(int w, int h, const char* title)
	: BaseWindow(w, h, title)
	, m_light({ 0.0f, 1.0f, 0.0f })
	, m_camera()
	, m_cameraController(m_camera)
	, m_renderConfigEditor(m_renderConfig)
	, m_world()
	, m_worldRenderer(m_world)
{}

void Window::SetupLight()
{
	m_light.SetDiffuseIntensity({ 0.6f, 0.6f, 0.6f, 1.0f });
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
		m_walkingForward = true;
	}
	if (key == GLFW_KEY_S)
	{
		m_walkingBackward = true;
	}
	if (key == GLFW_KEY_A)
	{
		m_walkingLeft = true;
	}
	if (key == GLFW_KEY_D)
	{
		m_walkingRight = true;
	}
}

void Window::OnKeyUp(int key, int scancode, int mods)
{
	if (key == GLFW_KEY_W)
	{
		m_walkingForward = false;
	}
	if (key == GLFW_KEY_S)
	{
		m_walkingBackward = false;
	}
	if (key == GLFW_KEY_A)
	{
		m_walkingLeft = false;
	}
	if (key == GLFW_KEY_D)
	{
		m_walkingRight = false;
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
	ImGui::Render();
}

bool Window::MouseMovePrevented()
{
	return m_showRenderConfig;
}

void Window::ApplyChanges()
{
	if (m_walkingForward)
	{
		m_cameraController.MoveForward(0.1);
	}
	else if (m_walkingBackward)
	{
		m_cameraController.MoveBackward(0.1);
	}
	else if (m_walkingLeft)
	{
		m_cameraController.MoveLeft(0.1);
	}
	else if (m_walkingRight)
	{
		m_cameraController.MoveRight(0.1);
	}

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