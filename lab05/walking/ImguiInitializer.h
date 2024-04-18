#pragma once

class ImguiInitializer final
{
public:
	explicit ImguiInitializer();

	ImguiInitializer(const ImguiInitializer&) = delete;
	ImguiInitializer& operator=(const ImguiInitializer&) = delete;

	~ImguiInitializer();
};