#pragma once
#include <memory>
#include "Image.h"
#include "IDrawingStrategy.h"

class DrawingStrategyBase : public IDrawingStrategy
{
public:
	DrawingStrategyBase(std::shared_ptr<QImage> image)
		: m_image(image)
		, m_settings({ 1, QColor::fromRgb(0x000000) })
	{
	}

	DrawingSettings GetSettings() override
	{
		return m_settings;
	}

	void SetSettings(DrawingSettings settings) override
	{
		m_settings = settings;
	}

protected:
	std::shared_ptr<QImage> m_image;
	DrawingSettings m_settings;
};