#pragma once
#include <memory>
#include <QMouseEvent>
#include "Image.h"
#include "IDrawingStrategy.h"
#include "IDrawingStrategyFactory.h"
#include "IOriginator.h"
#include "EditorMemento.h"
#include "History.h"

class Editor : public IOriginator<EditorMemento>
{
public:
	Editor(std::shared_ptr<QImage> image, IDrawingStrategyFactory& drawingStrategyFactory);

	void StartPaint(QMouseEvent* event);
	void Paint(QMouseEvent* event);
	void EndPaint(QMouseEvent* event);

	void Undo();
	void Redo();

	void SetImage(QImage image);
	void SetDrawingTool(std::string toolName);
	void SetDrawingSettings(DrawingSettings settings);

	void ClearImage();
	void SaveChanges();

	bool HasUnsavedChanges() const;
	DrawingSettings GetDrawingSettings() const;
	QImage const& GetImage() const;

	EditorMemento* Save();
	void Restore(EditorMemento* memento);

private:
	IDrawingStrategyFactory& m_drawingStrategyFactory;
	std::shared_ptr<IDrawingStrategy> m_drawingStrategy;
	std::shared_ptr<QImage> m_image;
	bool m_hasUnsavedChanges;
	History<EditorMemento> m_history;
};