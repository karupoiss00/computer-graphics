#pragma once
#include "Renderable.h"

class MobiusStrip : public IRenderable
{
public:
	MobiusStrip();
	void Render() const;
};