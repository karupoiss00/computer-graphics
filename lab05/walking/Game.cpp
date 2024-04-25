#include "Game.h"

Game::Game(IScreenProvider const& screenSizeProvider)
	: m_camera()
	, m_cameraController(m_camera)
	, m_renderConfigEditor(m_renderConfig)
	, m_world()
	, m_worldRenderer(m_world)
	, m_player(m_camera)
	, m_playerController(m_player, m_camera)
	, m_headLamp({ 0.0f, 0.0f, 0.0f })
	, m_globalLight({ 0.0f, 0.0f, 0.0f })
	, m_physics(m_world, 10.0)
	, m_skyTexture(
		L"./res/",
		L"pos_x_skybox.jpg",
		L"neg_x_skybox.jpg",
		L"pos_y_skybox.jpg",
		L"neg_y_skybox.jpg",
		L"pos_z_skybox.jpg",
		L"neg_z_skybox.jpg"
	)
	, m_skyBox(36, m_skyTexture)
	, m_playerState(m_player)
	, m_screenProvider(screenSizeProvider)
{
	SetupLight();
	SetupPhysics();
}

void Game::Setup()
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	m_headLamp.Apply(GL_LIGHT0);
	m_globalLight.Apply(GL_LIGHT1);
	m_skyTexture.Load();
}

void Game::Update(double dt)
{
	m_playerController.Update();
	m_physics.Update(dt);
	m_skyBox.SetPosition(m_player.GetPosition());
}

void Game::Draw()
{
	auto clearColor = m_renderConfig.m_backgroundColor;
	auto size = m_screenProvider.GetScreenSize();

	glClearColor(
		clearColor[0],
		clearColor[1],
		clearColor[2],
		clearColor[3]
	);

	ApplyProjection(size.x, size.y);

	ApplyFog();


	if (m_renderConfig.m_showSky)
	{
		m_skyBox.Render();
	}

	m_worldRenderer.Render();

	m_screenProvider.SetCursorVisible(m_showRenderConfig);
}

void Game::DrawUI()
{
	m_playerState.Render(m_renderConfig.m_showPlayerState);
	m_renderConfigEditor.Render(m_showRenderConfig);
	m_renderStats.Render(m_renderConfig.m_showStats);
}

void Game::OnKeyDown(int key, int scancode, int mods)
{
	if (key == GLFW_KEY_ESCAPE)
	{
		m_showRenderConfig = !m_showRenderConfig;
	}

	if (key == GLFW_KEY_SPACE)
	{
		m_player.SetJumping(true);
	}

	HandleMoving(key);
}

void Game::OnKeyUp(int key, int scancode, int mods)
{
	if (key == GLFW_KEY_SPACE)
	{
		m_player.SetJumping(false);
	}

	HandleStopMoving(key);
}

void Game::OnMouseMove(double x, double y)
{
	m_cameraController.MouseMoveHandler(
		m_screenProvider.GetScreenSize(),
		x,
		y,
		MouseMovePrevented()
	);
}

void Game::OnResize(int width, int height)
{
	ApplyProjection(width, height);
}

void Game::SetupLight()
{
	m_headLamp.SetDirection({ 0.0f, 0.0f, 1.0f });
	m_headLamp.SetDiffuseIntensity({ 0.9f, 0.9f, 0.9f, 1.0f });
	m_headLamp.SetAmbientIntensity({ 0.8f, 0.8f, 0.8f, 1.0f });
	m_headLamp.SetSpecularIntensity({ 0.2f, 0.2f, 0.2f, 1.0f });

	m_globalLight.SetDirection({ 0.0f, 1.0f, 0.0f });
	m_globalLight.SetDiffuseIntensity({ 0.9f, 0.9f, 0.9f, 1.0f });
	m_globalLight.SetAmbientIntensity({ 0.8f, 0.8f, 0.8f, 1.0f });
	m_globalLight.SetSpecularIntensity({ 0.2f, 0.2f, 0.2f, 1.0f });
}

void Game::SetupPhysics()
{
	m_physics.AddObject(&m_player);

	for (auto& obj : m_world.GetObjects())
	{
		m_physics.AddObject(obj);
	}
}


void Game::ApplyFog()
{
	if (!m_renderConfig.m_showFog)
	{
		glDisable(GL_FOG);
		return;
	}

	glEnable(GL_FOG);
	glFogi(GL_FOG_MODE, GL_EXP2);
	glFogfv(GL_FOG_COLOR, m_renderConfig.m_fogColor);
	glFogf(GL_FOG_DENSITY, m_renderConfig.m_fogDensity);
}

void Game::HandleMoving(int key)
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

void Game::HandleStopMoving(int key)
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

bool Game::MouseMovePrevented()
{
	return m_showRenderConfig;
}

void Game::ApplyProjection(int width, int height)
{
	float aspect = float(width) / float(height);
	float fov = m_renderConfig.m_fov * float(M_PI) / 180.0f;
	auto projectionMatrix = glm::perspective(fov, aspect, m_renderConfig.m_zNear, m_renderConfig.m_zFar);
	auto cameraMatrix = m_camera.GetWorldToViewMatrix();

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(&projectionMatrix[0][0]);
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(&cameraMatrix[0][0]);
}