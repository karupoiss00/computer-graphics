#include "EditorView.h"
#include "EditorController.h"
#include "Editor.h"
#include "Drawer.h"

EditorController::EditorController(EditorView* view, Editor* state)
	: m_view(view)
	, m_state(state)
{
	connect(m_view, &EditorView::MouseDownEvent, this, &EditorController::MouseDownHandler);
	connect(m_view, &EditorView::MouseMoveEvent, this, &EditorController::MouseMoveHandler);
	connect(m_view, &EditorView::MouseUpEvent, this, &EditorController::MouseUpHandler);
}

void EditorController::MouseDownHandler(QMouseEvent* event)
{
	m_state->StartPaint(event);
}

void EditorController::MouseMoveHandler(QMouseEvent* event)
{
	m_state->Paint(event);
}

void EditorController::MouseUpHandler(QMouseEvent* event)
{
	m_state->EndPaint(event);
}

void EditorController::SaveImage()
{
	m_state->SaveChanges();
}

void EditorController::ClearImage()
{
	m_state->ClearImage();
	m_view->update();
}

void EditorController::SetImage(QImage image)
{
	m_state->SetImage(image);
	auto size = image.size();
	m_view->resize(size.width(), size.height());
	m_view->update();
}

void EditorController::SetDrawingColor(QColor color)
{
	auto drawingSettings = m_state->GetDrawingSettings();

	drawingSettings.color = color;

	m_state->SetDrawingSettings(drawingSettings);
}

void EditorController::SetDrawingSize(int size)
{
	auto drawingSettings = m_state->GetDrawingSettings();

	drawingSettings.size = size;

	m_state->SetDrawingSettings(drawingSettings);
}

void EditorController::SetDrawingTool(std::string tool)
{
	m_state->SetDrawingTool(tool);
}

void EditorController::Undo()
{
	m_state->Undo();
	m_view->update();
}

void EditorController::Redo()
{
	m_state->Redo();
	m_view->update();
}

QImage const& EditorController::GetImage() const
{
	return m_state->GetImage();
}

DrawingSettings EditorController::GetDrawingSettings() const
{
	return m_state->GetDrawingSettings();
}