#pragma once
#include <QAction>

class EditorController;

class HistoryMenuController : public QObject
{
	Q_OBJECT
public:
	HistoryMenuController(QWidget* parent, EditorController* controller);

	QMenu* View();

	~HistoryMenuController();

private slots:
	void UndoHandler();
	void RedoHandler();

private:
	void InitUndoAction();
	void InitRedoAction();

	void CreateView();

	QMenu* m_view;

	QAction* m_undoAction;
	QAction* m_redoAction;

	EditorController* m_editorController;

	QWidget* m_parent;
};