#pragma once
#include "pch.h"
#include "Player.h"

class PlayerState
{
public:
	PlayerState(Player const& player);

	void Render(bool& opened) const;
private:
	Player const& m_player;
};