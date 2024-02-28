#pragma once
#include <QMouseEvent>
#include <QColor>

struct DrawingSettings
{
	int size;
	QColor color;
};

class IDrawingStrategy
{
public:
	virtual void StartPaint(QMouseEvent* event) = 0;
	virtual void Paint(QMouseEvent* event) = 0;
	virtual void EndPaint(QMouseEvent* event) = 0;

	virtual DrawingSettings GetSettings() = 0;
	virtual void SetSettings(DrawingSettings settings) = 0;

	virtual ~IDrawingStrategy() {};
};