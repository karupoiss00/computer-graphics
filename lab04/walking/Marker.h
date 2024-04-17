#pragma once
#include "PhysicalObject.h"

class Marker : public PhysicalObject
{
public:
	Marker()
		: PhysicalObject({
			{ 1, 15, 17 },
			{ 0.5, 0.5, 0.5 },
		}, 1.0, 1.0)
	{}
};