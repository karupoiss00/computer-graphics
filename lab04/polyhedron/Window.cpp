#include "pch.h"
#include "Window.h"

namespace
{
	constexpr double FOV_ANGLE = 60;
	constexpr double FIELD_OF_VIEW = FOV_ANGLE * M_PI / 180.0;
	constexpr double OBJECT_SIZE = 1.0;

	constexpr double Z_NEAR = 0.1;
	constexpr double Z_FAR = 10;
}

Window::Window(int w, int h, const char* title)
	: BaseWindow(w, h, title)
	, m_object(OBJECT_SIZE)
	, m_light({ 0.0f, 0.0f, 1.0f })
	, m_camera(DISTANCE_TO_ORIGIN)
{
	m_object.SetSideColor(DodecahedronSide::TOP_TOP, { 0.4, 0.4, 0.4, 1 });
	m_object.SetSideColor(DodecahedronSide::TOP_FIRST, { 1, 0.945, 0.702, 1 });
	m_object.SetSideColor(DodecahedronSide::TOP_SECOND, { 0.384, 0.812, 1, 1 });
	m_object.SetSideColor(DodecahedronSide::TOP_THIRD, { 1, 0.714, 0, 1 });
	m_object.SetSideColor(DodecahedronSide::TOP_FOURTH, { 0.714, 1, 0, 1 });
	m_object.SetSideColor(DodecahedronSide::TOP_FIFTH, { 1, 0.502, 0.753, 1 });
	m_object.SetSideColor(DodecahedronSide::BOTTOM_FIRST, { 0.11, 0.741, 0, 1 });
	m_object.SetSideColor(DodecahedronSide::BOTTOM_SECOND, { 0.784, 0.024, 1, 1 });
	m_object.SetSideColor(DodecahedronSide::BOTTOM_THIRD, { 1, 1, 0, 1 });
	m_object.SetSideColor(DodecahedronSide::BOTTOM_FOURTH, { 0.25, 0, 0.97, 1 });
	m_object.SetSideColor(DodecahedronSide::BOTTOM_FIFTH, { 0.97, 0, 0.25, 1 });
	m_object.SetSideColor(DodecahedronSide::BOTTOM_BOTTOM, { 1, 1, 1, 1 });
	m_object.SetSpecularColor({ 1, 1, 1, 1 });
	m_object.SetShininess(4.0f);

	m_light.SetDiffuseIntensity({ 0.6f, 0.6f, 0.6f, 1.0f });
	m_light.SetAmbientIntensity({ 0.3f, 0.3f, 0.3f, 1.0f });
	m_light.SetSpecularIntensity({ 0.3f, 0.3f, 0.3f, 1.0f });
}

void Window::OnMouseButton(int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_1)
	{
		m_leftButtonPressed = (action & GLFW_PRESS) != 0;
	}
}

void Window::OnMouseMove(double x, double y)
{
	const glm::dvec2 mousePos{ x, y };
	if (m_leftButtonPressed)
	{
		const auto windowSize = GetFramebufferSize();

		const auto mouseDelta = mousePos - m_mousePos;
		const double xAngle = mouseDelta.y * M_PI / windowSize.y;
		const double yAngle = mouseDelta.x * M_PI / windowSize.x;
		m_camera.Rotate(xAngle, yAngle);
	}
	m_mousePos = mousePos;
}

void Window::OnResize(int width, int height)
{
	double aspect = double(width) / double(height);
	auto projectionMatrix = glm::perspective(FIELD_OF_VIEW, aspect, Z_NEAR, Z_FAR);

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(&projectionMatrix[0][0]);
	glMatrixMode(GL_MODELVIEW);
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
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_camera.UpdateView();
	m_object.Draw();
}
