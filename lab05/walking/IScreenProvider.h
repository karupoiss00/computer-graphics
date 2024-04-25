#pragma once
#include <glm/glm.hpp>

class IScreenProvider
{
public:
	virtual glm::ivec2 GetScreenSize() const = 0;
	virtual void SetCursorVisible(bool visible) const = 0;
};