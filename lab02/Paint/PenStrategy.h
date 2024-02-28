#pragma once
#include <QWidget>
#include <QImage>
#include <algorithm>
#include "DrawingStrategyBase.h"
#include "Drawer.h"

class PenStrategy : public DrawingStrategyBase 
{
public :
	PenStrategy(std::shared_ptr<QImage> image, QWidget* view)
		: DrawingStrategyBase(image)
		, m_drawing(false)
		, m_view(view)
	{}

	void StartPaint(QMouseEvent* event) override
	{
		if (event->button() == Qt::LeftButton) 
		{
			m_drawing = true;
			m_lastPoint = ClampPoint(event->pos());
			Draw(event);
		}
	}

	void Paint(QMouseEvent* event) override
	{
		if (!m_drawing)
		{
			return;
		}

		if (event->buttons() & Qt::LeftButton)
		{
			Draw(event);
		}
	}

	void EndPaint(QMouseEvent* event) override
	{
		m_drawing = false;
	}

private:
	QPoint ClampPoint(QPoint const& point)
	{
		auto imageSize = m_image->size();
		return {
			std::clamp(point.x(), 0, imageSize.width()),
			std::clamp(point.y(), 0, imageSize.height())
		};
	};

	void Draw(QMouseEvent* event)
	{
		auto pos = ClampPoint(event->pos());
		auto radius = (m_settings.size / 2) + 2;
		DrawLine(
			*m_image,
			{ m_lastPoint.x(), m_lastPoint.y() },
			{ pos.x(), pos.y() },
			m_settings.color.rgb(),
			m_settings.size);

		auto dirtyRect = QRect(m_lastPoint, pos).normalized().adjusted(-radius, -radius, +radius, +radius);

		m_view->update(dirtyRect);

		m_lastPoint = pos;
	}


	bool m_drawing;
	QPoint m_lastPoint;
	QWidget* m_view;
};