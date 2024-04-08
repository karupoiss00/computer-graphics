#pragma once

struct RenderConfig
{
	RenderConfig()
		: m_fov(60.0f)
		, m_zNear(0.1f)
		, m_zFar(20.0f)
	{
		m_backgroundColor[0] = 0.65f;
		m_backgroundColor[1] = 0.85f;
		m_backgroundColor[2] = 1.0f;
		m_backgroundColor[3] = 1.0f;
	}

	float m_fov;
	float m_zNear;
	float m_zFar;
	float m_backgroundColor[4];
};