#pragma once
#include <glm/glm.hpp>

class IGravityObject
{
public:
	IGravityObject() = default;

	virtual double GetVerticalSpeed() = 0;
	virtual void SetVerticalSpeed(double speed) = 0;
	virtual bool CanDrop() = 0;
	virtual double GetElasticity() = 0;

	virtual ~IGravityObject() = default;
};