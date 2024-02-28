#pragma once
#include <QPainter>
#include <QWidget>
#include <algorithm>

#include "Drawer.h"
#include "DrawingStrategyBase.h"
#include "IEditorView.h"

class DraftDrawingStrategy : public DrawingStrategyBase
{
public:
	DraftDrawingStrategy(std::shared_ptr<QImage> image, IEditorView* view)
		: DrawingStrategyBase(image)
		, m_drawing(false)
		, m_view(view)
		, m_draftImage(std::make_shared<QImage>(*image))
	{
	}

	void StartPaint(QMouseEvent* event) override
	{
		if (event->button() == Qt::LeftButton)
		{
			m_drawing = true;
			m_startPoint = ClampPoint(event->pos());
			*m_draftImage = *m_image;
			m_view->SetImage(m_draftImage);
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
			*m_draftImage = *m_image;

			m_view->update();

			m_lastPoint = ClampPoint(event->pos());

			Draw(*m_draftImage);

			m_view->update(QRect(m_startPoint, m_lastPoint));
		}
	}

	void EndPaint(QMouseEvent* event) override
	{
		m_lastPoint = event->pos();

		Draw(*m_image);

		m_view->SetImage(m_image);
		m_view->update();
		m_drawing = false;
	}

protected:
	virtual void Draw(QImage& image) = 0;

	QPoint const& GetStartPoint() const
	{
		return m_startPoint;
	};

	QPoint const& GetLastPoint() const
	{
		return m_lastPoint;
	};

private:
	QPoint ClampPoint(QPoint const& point)
	{
		auto imageSize = m_image->size();
		return {
			std::clamp(point.x(), 0, imageSize.width()),
			std::clamp(point.y(), 0, imageSize.height())
		};
	};

	bool m_drawing;

	QPoint m_startPoint;
	QPoint m_lastPoint;

	std::shared_ptr<QImage> m_draftImage;

	IEditorView* m_view;
};
