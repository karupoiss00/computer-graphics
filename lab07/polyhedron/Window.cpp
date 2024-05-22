#include <iostream>
#include "pch.h"
#include "Window.h"

Window::Window(int w, int h, const char* title)
	: BaseWindow(w, h, title)
	, m_light({ 0.0f, 0.0f, 1.0f })
	, m_camera(DISTANCE_TO_ORIGIN)
	, m_cameraController(m_camera)
	, m_objectConfig([this]() {
		m_object->Reload();
	})
	, m_dodecahedron(m_objectConfig.m_size)
	, m_mobiusStrip(m_objectConfig.m_size)
	, m_canabola(m_objectConfig.m_size)
	, m_morphingObject(m_objectConfig.m_size)
	, m_object(&m_emptyObject)
	, m_renderConfigEditor(m_renderConfig)
	, m_objectConfigEditor(m_objectConfig)
{
	SetupDodecahedron();
	SetupLight();

	m_objectsMap.insert({ "dodecahedron", &m_dodecahedron });
	m_objectsMap.insert({ "mobius strip", &m_mobiusStrip });
	m_objectsMap.insert({ "canabola", &m_canabola });
	m_objectsMap.insert({ "flag", &m_flag });
	m_objectsMap.insert({ "morphing object", &m_morphingObject });
}

Window::~Window() {
}

void Window::SetupLight()
{
	m_light.SetDiffuseIntensity({ 0.6f, 0.6f, 0.6f, 1.0f });
	m_light.SetAmbientIntensity({ 0.3f, 0.3f, 0.3f, 1.0f });
	m_light.SetSpecularIntensity({ 0.3f, 0.3f, 0.3f, 1.0f });
}

void Window::SetupDodecahedron()
{
	m_dodecahedron.SetSideColor(DodecahedronSide::TOP_TOP, { 0.4, 0.4, 0.4, 1 });
	m_dodecahedron.SetSideColor(DodecahedronSide::TOP_FIRST, { 1, 0.945, 0.702, 1 });
	m_dodecahedron.SetSideColor(DodecahedronSide::TOP_SECOND, { 0.384, 0.812, 1, 1 });
	m_dodecahedron.SetSideColor(DodecahedronSide::TOP_THIRD, { 1, 0.714, 0, 1 });
	m_dodecahedron.SetSideColor(DodecahedronSide::TOP_FOURTH, { 0.714, 1, 0, 1 });
	m_dodecahedron.SetSideColor(DodecahedronSide::TOP_FIFTH, { 1, 0.502, 0.753, 1 });
	m_dodecahedron.SetSideColor(DodecahedronSide::BOTTOM_FIRST, { 0.11, 0.741, 0, 1 });
	m_dodecahedron.SetSideColor(DodecahedronSide::BOTTOM_SECOND, { 0.784, 0.024, 1, 1 });
	m_dodecahedron.SetSideColor(DodecahedronSide::BOTTOM_THIRD, { 1, 1, 0, 1 });
	m_dodecahedron.SetSideColor(DodecahedronSide::BOTTOM_FOURTH, { 0.25, 0, 0.97, 1 });
	m_dodecahedron.SetSideColor(DodecahedronSide::BOTTOM_FIFTH, { 0.97, 0, 0.25, 1 });
	m_dodecahedron.SetSideColor(DodecahedronSide::BOTTOM_BOTTOM, { 1, 1, 1, 1 });
	m_dodecahedron.SetSpecularColor({ 1, 1, 1, 1 });
	m_dodecahedron.SetShininess(4.0f);
}

void Window::OnMouseButton(int button, int action, int mods)
{
	if (MouseMovePrevented())
	{
		return;
	}

	m_cameraController.MouseDownHandler(button, action, mods);
}

void Window::OnMouseMove(double x, double y)
{
	m_cameraController.MouseMoveHandler(GetFramebufferSize(), x, y);
}

void Window::OnResize(int width, int height)
{
	ApplyProjectionChanges(width, height);
}

void Window::OnRunStart()
{
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
	glClearColor(
		clearColor[0],
		clearColor[1],
		clearColor[2],
		clearColor[3]
	);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_camera.UpdateView();

	m_object->Render();
}


void Window::DrawGUI(int width, int height)
{
	ImGui::NewFrame();
	m_renderConfigEditor.Render();
	m_objectConfigEditor.Render();
	ImGui::Render();
}

bool Window::MouseMovePrevented()
{
	return ImGui::GetIO().WantCaptureMouse;
}

void Window::ApplyChanges()
{
	auto size = GetFramebufferSize();

	ApplyDodecahedronChanges();
	ApplyMobiusStripChanges();
	ApplyCanabolaChanges();
	ApplyFlagChanges();
	ApplyMorphingObjectChanges();
	ApplyObjectChanges();
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

void Window::ApplyDodecahedronChanges()
{
	m_dodecahedron.SetObjectSize(m_objectConfig.m_size);
}

void Window::ApplyMobiusStripChanges()
{
	m_mobiusStrip.SetObjectSize(m_objectConfig.m_size);
}

void Window::ApplyCanabolaChanges()
{
	m_canabola.SetObjectSize(m_objectConfig.m_size);
}

void Window::ApplyFlagChanges()
{
	m_flag.SetObjectSize(m_objectConfig.m_size);
}

void Window::ApplyMorphingObjectChanges()
{
	m_morphingObject.SetObjectSize(m_objectConfig.m_size);
	m_morphingObject.SetMorphStep(m_objectConfig.m_animationTick);
}

void Window::ApplyObjectChanges()
{
	auto selectedObject = m_objectConfig.m_selectedObject;

	auto pos = m_objectsMap.find(selectedObject);

	if (pos == m_objectsMap.end())
	{
		m_object = &m_emptyObject;
	}
	else
	{
		m_object = pos->second;
	}
}
