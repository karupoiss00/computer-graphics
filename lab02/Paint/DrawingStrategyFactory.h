#pragma once
#include <QWidget>
#include <stdexcept>
#include "IDrawingStrategyFactory.h"
#include "PenStrategy.h"
#include "LineStrategy.h"
#include "CircleStrategy.h"
#include "Image.h"
#include "IEditorView.h"

class DrawingStrategyFactory : public IDrawingStrategyFactory
{
public:
	DrawingStrategyFactory()
		: m_penStrategy(nullptr)
		, m_lineStrategy(nullptr)
		, m_circleStrategy(nullptr)
	{
	}

	DrawingStrategyFactory(std::shared_ptr<QImage> image, IEditorView* view)
		: m_penStrategy(std::make_shared<PenStrategy>(image, view))
		, m_lineStrategy(std::make_shared<LineStrategy>(image, view))
		, m_circleStrategy(std::make_shared<CircleStrategy>(image, view))
	{

	}

	std::shared_ptr<IDrawingStrategy> GetStrategy(std::string type) override
	{
		if (type == "pen")
		{
			return m_penStrategy;
		}

		if (type == "line")
		{
			return m_lineStrategy;
		}

		if (type == "circle")
		{
			return m_circleStrategy;
		}


		throw std::invalid_argument("unknown tool type");
	}

private:
	std::shared_ptr<PenStrategy> m_penStrategy;
	std::shared_ptr<LineStrategy> m_lineStrategy;
	std::shared_ptr<CircleStrategy> m_circleStrategy;
};