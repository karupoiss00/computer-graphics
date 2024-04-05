#pragma once
#include "pch.h"
#include "ObjectConfig.h"

class ObjectConfigEditor
{
public:
	ObjectConfigEditor(ObjectConfig& cfg);

	void Render();
private:
	ObjectConfig& m_config;
	bool m_opened;
};