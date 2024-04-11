#pragma once

class IRenderable
{
public:
	virtual void Render() const = 0;
	virtual ~IRenderable() = default;
};