#pragma once
#include "pch.h"
#include "RenderConfig.h"

class RenderConfigEditor
{
public:
	RenderConfigEditor(RenderConfig& cfg);

	void Render();
private:
	RenderConfig& m_config;
};