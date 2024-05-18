#pragma once
#include <functional>
#include <string>

struct ObjectConfig
{
	ObjectConfig(std::function<void()> onReload = []() {})
		: m_size(1.0f)
		, m_selectedObject("canabola")
		, m_onReloadFn(onReload)
	{
		
	}

	float m_size;
	std::string m_selectedObject;
	std::function<void()> m_onReloadFn;
};