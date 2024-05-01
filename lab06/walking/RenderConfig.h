#pragma once

struct RenderConfig
{
	RenderConfig()
		: m_fov(60.0f)
		, m_zNear(0.001f)
		, m_zFar(100.0f)
	{
		m_backgroundColor[0] = 0.0f;
		m_backgroundColor[1] = 0.0f;
		m_backgroundColor[2] = 0.0f;
		m_backgroundColor[3] = 1.0f;
		m_showStats = false;
		m_showFog = false;
		m_showSky = true;
		m_fogColor[0] = 1.0f;
		m_fogColor[1] = 1.0f;
		m_fogColor[2] = 1.0f;
		m_fogColor[3] = 1.0f;
		m_fogDensity = 0.05f;
	}

	float m_fov;
	float m_zNear;
	float m_zFar;
	float m_backgroundColor[4];
	bool m_showStats;
	bool m_showPlayerState;
	bool m_showFog;
	bool m_showSky;
	float m_fogColor[4];
	float m_fogDensity;
};