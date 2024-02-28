#pragma once
#include <QAction>
#include <QActionGroup>

class EditorController;

class ToolsMenuController : public QObject
{
	Q_OBJECT
public:
	ToolsMenuController(QWidget* parent, EditorController* controller);

	QMenu* View();

	~ToolsMenuController();

private slots:
	void DrawColorChangeHandler();
	void DrawSizeChangeHandler();
	void SetPenToolHandler();
	void SetLineToolHandler();
	void SetEllipseToolHandler();
	void ClearImageHandler();

private:
	void InitSetDrawSizeAction();
	void InitSetDrawColorAction();
	void InitSetPenToolAction();
	void InitSetLineToolAction();

	void InitSetEllipseToolAction();
	void InitClearScreenAction();

	void CreateView();

	QMenu* m_view;

	QAction* m_drawColorChangeAction;
	QAction* m_drawSizeChangeAction;
	QAction* m_clearScreenAction;

	QActionGroup* m_toolsActionGroup;	
	QAction* m_setPenToolAction;
	QAction* m_setLineToolAction;
	QAction* m_setEllipseToolAction;

	EditorController* m_editorController;

	QWidget* m_parent;
};