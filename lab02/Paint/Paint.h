#pragma once
#include <memory>
#include <optional>
#include <QtWidgets/QMainWindow>
#include <QList>
#include <QGridLayout>

#include "DrawingStrategyFactory.h"
#include "FileMenuController.h"
#include "ToolsMenuController.h"
#include "HistoryMenuController.h"

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

class Image;
class Editor;
class EditorView;
class EditorController;

class Paint : public QMainWindow
{
	Q_OBJECT

public:
	Paint();
	~Paint();

protected:
	void closeEvent(QCloseEvent* event) override;
private slots:
	void OpenFileHandler();
	void SaveFileHandler(const QByteArray& fileFormat);

private:
	void CreateUI();

	std::optional<bool> HasUnsavedChanges();
	bool SaveFile(const QByteArray& fileFormat);

	std::shared_ptr<QImage> m_image;

	DrawingStrategyFactory m_drawingStrategyFactory;

	Editor* m_editor;
	EditorController* m_editorController;
	EditorView* m_editorView;

	FileMenuController* m_fileMenuController;
	ToolsMenuController* m_toolsMenuController;
	HistoryMenuController* m_historyMenuController;

	QGridLayout* m_widgetsLayout;
};

#endif