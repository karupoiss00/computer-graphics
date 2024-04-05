#pragma once
#include "BaseWindow.h"
#include "DirectLight.h"
#include "Dodecahedron.h"
#include "Camera.h"
#include "RenderConfigEditor.h"
#include "RenderConfig.h"
#include "ObjectConfigEditor.h"
#include "ObjectConfig.h"
#include "EmptyObject.h"
#include "MobiusStrip.h"

class Window : public BaseWindow
{
public:
	Window(int w, int h, const char* title);

private:
	static constexpr double DISTANCE_TO_ORIGIN = 2;

	void SetupLight();

	void SetupDodecahedron();

	bool MouseDownPrevented();

	void OnMouseButton(int button, int action, [[maybe_unused]] int mods) override;

	void OnMouseMove(double x, double y) override;

	void OnResize(int width, int height) override;

	void OnRunStart() override;

	void Draw(int width, int height) override;
	
	void DrawGUI(int width, int height) override;

	void ApplyProjectionChanges(int width, int height);

	void ApplyObjectChanges();

	void ApplyDodecahedronChanges();

	void ApplyMobiusStripChanges();

	void ApplyChanges();


	RenderConfigEditor m_renderConfigEditor;
	RenderConfig m_renderConfig;

	ObjectConfigEditor m_objectConfigEditor;
	ObjectConfig m_objectConfig;

	DirectLight m_light;
	Camera m_camera;

	EmptyObject m_emptyObject;
	Dodecahedron m_dodecahedron;
	MobiusStrip m_mobiusStrip;
	IRenderable* m_object;

	bool m_leftButtonPressed = false;
	glm::dvec2 m_mousePos = {};
};