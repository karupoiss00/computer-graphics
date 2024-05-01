#pragma once
#include <glm/glm.hpp>
#include "Direction.h"

class IViewDirectionProvider
{
public:
	virtual glm::dvec3 GetDirectionProjection(Direction dir) = 0;
	virtual ~IViewDirectionProvider() = default;
};