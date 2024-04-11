#pragma once
#include <vector>
#include "GravityObject.h"

class Gravity
{
public:
	Gravity(double gConst);

	void AddObject(IGravityObject* object);
	void RemoveObject(IGravityObject* object);
	void Update(double deltaTime);

private:
	double m_gConst;
	std::vector<IGravityObject*> m_objects;
};