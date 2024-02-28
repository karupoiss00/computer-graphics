#include <QImage>
#include "Editor.h"

const std::string DEFAULT_TOOL = "pen";
const Color CLEAR_COLOR = 0xFFFFFF; 

Editor::Editor(std::shared_ptr<QImage> image, IDrawingStrategyFactory& drawingStrategyFactory)
	: m_drawingStrategyFactory(drawingStrategyFactory)
	, m_hasUnsavedChanges(false)
	, m_image(image)
	, m_history(this)
{
	SetDrawingTool(DEFAULT_TOOL);
}

void Editor::StartPaint(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		m_history.Save();
		m_hasUnsavedChanges = true;
	}

	m_drawingStrategy->StartPaint(event);
}

void Editor::Paint(QMouseEvent* event)
{
	m_drawingStrategy->Paint(event);
}

void Editor::EndPaint(QMouseEvent* event)
{
	m_drawingStrategy->EndPaint(event);
}

DrawingSettings Editor::GetDrawingSettings() const
{
	return m_drawingStrategy->GetSettings();
}

void Editor::Undo()
{
	m_history.Undo();
}

void Editor::Redo()
{
	m_history.Redo();
}

void Editor::ClearImage()
{
	m_history.Save();
	m_image->fill(CLEAR_COLOR);
	m_hasUnsavedChanges = true;
}

void Editor::SaveChanges()
{
	m_hasUnsavedChanges = false;
}

void Editor::SetImage(QImage image)
{
	*m_image = image;
}

QImage const& Editor::GetImage() const
{
	return *m_image;
}

void Editor::SetDrawingTool(std::string toolName)
{
	m_drawingStrategy = m_drawingStrategyFactory.GetStrategy(toolName);
}

void Editor::SetDrawingSettings(DrawingSettings settings)
{
	m_drawingStrategy->SetSettings(settings);
}

bool Editor::HasUnsavedChanges() const
{
	return m_hasUnsavedChanges;
}

EditorMemento* Editor::Save()
{
	return new EditorMemento({*m_image, m_hasUnsavedChanges});
}

void Editor::Restore(EditorMemento* memento)
{
	auto state = memento->State();

	*m_image = state.image;
	m_hasUnsavedChanges = state.hasUnsavedChanges;
}