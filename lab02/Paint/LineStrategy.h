#pragma once
#include <algorithm>
#include <QWidget>
#include <QPainter>
#include "DraftDrawingStrategy.h"

#include "Drawer.h"
#include "DrawingStrategyBase.h"
#include "IEditorView.h"

class LineStrategy : public DraftDrawingStrategy
{
public:
	LineStrategy(std::shared_ptr<QImage> image, IEditorView* view)
		: DraftDrawingStrategy(image, view)
	{
	
	}

protected:
	void Draw(QImage& image) override
	{
		auto startPoint = GetStartPoint();
		auto endPoint = GetLastPoint();

		DrawLine
		(
			image,
			{ startPoint.x(), startPoint.y() },
			{ endPoint.x(), endPoint.y() },
			m_settings.color.rgb(),
			m_settings.size
		);
	}
};