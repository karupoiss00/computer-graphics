#pragma once
#include "Renderable.h"

class EmptyObject : public IRenderable
{
public:
	EmptyObject() {};
	void Render() const {};
};