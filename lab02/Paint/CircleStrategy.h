#pragma once
#include "DraftDrawingStrategy.h"
#include <QPainter>
#include <QWidget>
#include <algorithm>

#include "Drawer.h"
#include "DrawingStrategyBase.h"
#include "IEditorView.h"

class CircleStrategy : public DraftDrawingStrategy
{
public:
	CircleStrategy(std::shared_ptr<QImage> image, IEditorView* view)
		: DraftDrawingStrategy(image, view)
	{
	}

protected:
	void Draw(QImage& image) override
	{
		auto rawStartPoint = GetStartPoint();
		auto rawEndPoint = GetLastPoint();
		auto rect = QRect::span(rawStartPoint, rawEndPoint);
		auto startPoint = rect.topLeft();
		auto endPoint = rect.bottomRight();

		Point center = { (startPoint.x() + endPoint.x()) / 2, (startPoint.y() + endPoint.y()) / 2 };

		int rx = (endPoint.x() - startPoint.x()) / 2;
		int ry = (endPoint.y() - startPoint.y()) / 2;

		DrawCircle
		(
			image,
			center,
			std::min(rx, ry),
			m_settings.color.rgb(),
			m_settings.size
		);
	}
};