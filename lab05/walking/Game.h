#pragma once
#include "IView.h"
#include "IScreenProvider.h"
#include "DirectLight.h"
#include "Camera.h"
#include "CameraController.h"
#include "RenderConfigEditor.h"
#include "RenderConfig.h"
#include "World.h"
#include "WorldRenderer.h"
#include "Player.h"
#include "PlayerController.h"
#include "RenderStats.h"
#include "PlayerState.h"
#include "Physics.h"
#include "Skybox.h"

class Game : public IView
{
public:
	Game(IScreenProvider const& screenSizeProvider);

	void Setup();
	void Update(double dt);
	void Draw();
	void DrawUI();

	void OnKeyDown(int key, int scancode, int mods);
	void OnKeyUp(int key, int scancode, int mods);
	void OnMouseMove(double x, double y);
	void OnResize(int width, int height);
private:
	void SetupLight();
	void SetupPhysics();

	void ApplyFog();

	void HandleMoving(int key);
	void HandleStopMoving(int key);

	bool MouseMovePrevented();

	void ApplyProjection(int width, int height);

	RenderConfigEditor m_renderConfigEditor;
	RenderConfig m_renderConfig;
	RenderStats m_renderStats;
	PlayerState m_playerState;

	Camera m_camera;
	World m_world;
	Player m_player;
	Physics m_physics;

	CameraController m_cameraController;
	PlayerController m_playerController;

	DirectLight m_headLamp;
	DirectLight m_globalLight;
	WorldRenderer m_worldRenderer;
	SkyBox m_skyBox;

	CubemapTexture m_skyTexture;

	bool m_showRenderConfig;

	IScreenProvider const& m_screenProvider;
};