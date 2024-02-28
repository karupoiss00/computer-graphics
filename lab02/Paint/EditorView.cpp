#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include "EditorView.h"
#include "QImageToImage.h"

EditorView::EditorView(QWidget* parent, std::shared_ptr<QImage> image)
	: IEditorView(parent)
	, m_image(image)
{
	setAttribute(Qt::WA_StaticContents);
}

void EditorView::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);

	QRect dirtyRect = event->rect();
	painter.drawImage(dirtyRect, *m_image, dirtyRect);
}

void EditorView::mousePressEvent(QMouseEvent* event)
{
	emit MouseDownEvent(event);
}

void EditorView::mouseMoveEvent(QMouseEvent* event) 
{
	emit MouseMoveEvent(event);
}

void EditorView::mouseReleaseEvent(QMouseEvent* event)
{
	emit MouseUpEvent(event);
}

void EditorView::SetImage(std::shared_ptr<QImage> image)
{
	m_image = image;
	update();
}