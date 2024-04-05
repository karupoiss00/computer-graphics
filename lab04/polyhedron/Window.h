#pragma once
#include "BaseWindow.h"
#include "DirectLight.h"
#include "Dodecahedron.h"
#include "Camera.h"

class Window : public BaseWindow
{
public:
	Window(int w, int h, const char* title);

private:
	static constexpr double DISTANCE_TO_ORIGIN = 2;

	void OnMouseButton(int button, int action, [[maybe_unused]] int mods) override;

	void OnMouseMove(double x, double y) override;

	void RotateCamera(double xAngleRadians, double yAngleRadians);

	void OnResize(int width, int height) override;

	void OnRunStart() override;

	void Draw(int width, int height) override;

	Dodecahedron m_object;
	DirectLight m_light;
	Camera m_camera;


	bool m_leftButtonPressed = false;
	glm::dvec2 m_mousePos = {};
	
};