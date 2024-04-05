#pragma once
#include "Renderable.h"

class MobiusStrip : public IRenderable
{
public:
	MobiusStrip(float size);
	void SetObjectSize(float size);
	void Render() const;
private:
	float m_size;
};