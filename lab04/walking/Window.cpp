#include <iostream>
#include "pch.h"
#include "Window.h"

Window::Window(int w, int h, const char* title)
	: BaseWindow(w, h, title)
	, m_camera()
	, m_cameraController(m_camera)
	, m_renderConfigEditor(m_renderConfig)
	, m_world()
	, m_worldRenderer(m_world)
	, m_player(m_camera)
	, m_playerController(m_player, m_camera)
	, m_light({ 0.0f, 0.0f, 0.0f })
	, m_physics(m_world, 10.0)
{
	SetupLight();
	SetupPhysics();
}

void Window::SetupLight()
{
	m_light.SetDirection({ 0.0f, 10.0f, 0.0f });
	m_light.SetDiffuseIntensity({ 0.9f, 0.9f, 0.9f, 1.0f });
	m_light.SetAmbientIntensity({ 0.8f, 0.8f, 0.8f, 1.0f });
	m_light.SetSpecularIntensity({ 0.2f, 0.2f, 0.2f, 1.0f });
}

void Window::SetupPhysics()
{
	m_physics.AddObject(&m_player);
	
	for (auto& obj : m_world.GetObjects())
	{
		m_physics.AddObject(obj);
	}
}

void Window::OnKeyDown(int key, int scancode, int mods)
{
	if (key == GLFW_KEY_ESCAPE)
	{
		m_showRenderConfig = !m_showRenderConfig;
	}

	if (key == GLFW_KEY_SPACE)
	{
		m_player.Jump(10);
	}

	HandleMoving(key);
}

void Window::OnKeyRepeat(int key, int scancode, int mods)
{
	HandleMoving(key);
}

void Window::OnKeyUp(int key, int scancode, int mods)
{
	HandleStopMoving(key);
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
	UpdatePhysics();

	UpdateLight();

	ApplyChanges();

	Clear();

	ShowCursor(m_showRenderConfig);

	LoadCameraMatrix();

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
	m_playerController.Update();

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

void Window::UpdateLight()
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	double maxAngle = m_camera.GetMaxVerticalAngle();
	double minAngle = m_camera.GetMinVerticalAngle();
	double angle = m_camera.GetVerticalAngle();
	double zCamera = (angle - 90) / (maxAngle - minAngle) / 2;

	m_light.SetDirection({ 0.0f, 10.0f, 10.0f * zCamera });
	m_light.Apply(GL_LIGHT0);
	glPopMatrix();
}


void Window::UpdatePhysics()
{
	auto deltaTime = GetEllapsedTime();
	m_physics.Update(deltaTime);
}

void Window::Clear()
{
	auto clearColor = m_renderConfig.m_backgroundColor;
	glClearColor(
		clearColor[0],
		clearColor[1],
		clearColor[2],
		clearColor[3]
	);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::LoadCameraMatrix()
{
	auto cameraMatrix = m_camera.GetWorldToViewMatrix();
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(&cameraMatrix[0][0]);
}

void Window::HandleMoving(int key)
{
	if (key == GLFW_KEY_W)
	{
		m_player.SetForwardMovement(3);
	}
	if (key == GLFW_KEY_S)
	{
		m_player.SetBackwardMovement(3);
	}
	if (key == GLFW_KEY_A)
	{
		m_player.SetStrafeLeftMovement(2);
	}
	if (key == GLFW_KEY_D)
	{
		m_player.SetStrafeRightMovement(2);
	}
}

void Window::HandleStopMoving(int key)
{
	if (key == GLFW_KEY_W)
	{
		m_player.SetForwardMovement(0);
	}
	if (key == GLFW_KEY_S)
	{
		m_player.SetBackwardMovement(0);
	}
	if (key == GLFW_KEY_A)
	{
		m_player.SetStrafeLeftMovement(0);
	}
	if (key == GLFW_KEY_D)
	{
		m_player.SetStrafeRightMovement(0);
	}
}