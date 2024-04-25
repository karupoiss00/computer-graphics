﻿#pragma once
#include <map>
#include <string>
#include <functional>
#include "BaseWindow.h"
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

class Window : public BaseWindow
{
public:
	Window(int w, int h, const char* title);

private:
	void SetupLight();

	void SetupPhysics();

	void ApplyFog();

	void UpdatePhysics();

	void UpdateSkybox();

	bool MouseMovePrevented();

	void OnKeyDown(int key, int scancode, int mods);

	void OnKeyUp(int key, int scancode, int mods);

	void OnMouseMove(double x, double y) override;

	void OnResize(int width, int height) override;

	void OnRunStart() override;

	void Clear();

	void LoadCameraMatrix();

	void Draw(int width, int height) override;
	
	void DrawGUI(int width, int height) override;

	void ApplyProjectionChanges(int width, int height);

	void ApplyChanges();

	void HandleMoving(int key);

	void HandleStopMoving(int key);

	RenderConfigEditor m_renderConfigEditor;
	RenderConfig m_renderConfig;
	RenderStats m_renderStats;
	PlayerState m_playerState;

	Physics m_physics;
	SkyBox m_skyBox;
	CubemapTexture m_skyTexture;

	DirectLight m_headLamp;
	DirectLight m_globalLight;

	CameraController m_cameraController;
	Camera m_camera;

	World m_world;
	WorldRenderer m_worldRenderer;

	Player m_player;
	PlayerController m_playerController;

	bool m_showRenderConfig;
};