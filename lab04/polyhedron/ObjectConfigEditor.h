#pragma once
#include "pch.h"
#include "ObjectConfig.h"

class ObjectConfigEditor
{
public:
	ObjectConfigEditor(ObjectConfig& cfg);

	void Render();
private:
	void SelectedObjectCombo();

	ObjectConfig& m_config;
};