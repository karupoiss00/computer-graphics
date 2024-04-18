#pragma once
#include "PhysicalObject.h"

class Marker : public PhysicalObject
{
public:
	Marker()
		: PhysicalObject({
			{ 1.5, 1.4, 16.5 },
			{ 0.6, 0.6, 0.6 },
		}, 1.0, 1.0)
	{}
};