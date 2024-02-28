#pragma once
#ifndef SCRIBBLEAREA_H
#define SCRIBBLEAREA_H

#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>
#include "Document.h"
#include "IEditorView.h"

class EditorView : public IEditorView
{
	Q_OBJECT

public:
	EditorView(QWidget* parent, std::shared_ptr<QImage> image);

	void SetImage(std::shared_ptr<QImage> image) override;

signals:
	void MouseDownEvent(QMouseEvent* event);
	void MouseMoveEvent(QMouseEvent* event);
	void MouseUpEvent(QMouseEvent* event);

protected:
	void paintEvent(QPaintEvent* event) override;

	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;

private:
	std::shared_ptr<QImage> m_image;
};

#endif