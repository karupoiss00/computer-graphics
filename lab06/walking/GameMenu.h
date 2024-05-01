#pragma once
#include <functional>
#include "IScreenProvider.h"
#include "pch.h"

class GameMenu
{
public:
	GameMenu(IScreenProvider const& screenProvider, std::function<void()> onGoToMainMenu);

	void Render(bool& opened) const;
private:
	std::function<void()> m_onGoToMainMenu;
	IScreenProvider const& m_screenProvider;
};