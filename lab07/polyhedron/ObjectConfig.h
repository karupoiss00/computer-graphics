#pragma once
#include <functional>
#include <string>

struct ObjectConfig
{
	ObjectConfig(std::function<void()> onReload = []() {})
		: m_size(1.0f)
		, m_animationTick(0)
		, m_selectedObject("morphing object")
		, m_onReloadFn(onReload)
	{
		
	}

	float m_size;
	float m_animationTick;
	std::string m_selectedObject;
	std::function<void()> m_onReloadFn;
};