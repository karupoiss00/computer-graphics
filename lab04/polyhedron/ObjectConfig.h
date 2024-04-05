#pragma once
#include <string>

struct ObjectConfig
{
	ObjectConfig()
		: m_size(1.0f)
		, m_selectedObject("dodecahedron")
	{
		
	}

	float m_size;
	std::string m_selectedObject;
};