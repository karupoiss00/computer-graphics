#pragma once
#include <functional>
#include <memory>
#include <QtWidgets>
#include <QColor>
#include <QPoint>
#include "Image.h"
#include "IDrawingStrategy.h"

class EditorView;
class Editor;

class EditorController : public QObject
{
	Q_OBJECT
public:
	EditorController(EditorView* view, Editor* state);

	void SetImage(QImage image);

	void SetDrawingColor(QColor color);
	void SetDrawingSize(int size);
	void SetDrawingTool(std::string tool);

	void Undo();
	void Redo();

	void ClearImage();
	void SaveImage();

	QImage const& GetImage() const;
	DrawingSettings GetDrawingSettings() const;

private slots:
	void MouseDownHandler(QMouseEvent* event);
	void MouseMoveHandler(QMouseEvent* event);
	void MouseUpHandler(QMouseEvent* event);

private:
	EditorView* m_view;
	Editor* m_state;
};