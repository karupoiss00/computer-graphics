#include "HistoryMenuController.h"
#include "EditorController.h"

HistoryMenuController::HistoryMenuController(QWidget* parent, EditorController* controller)
	: m_editorController(controller)
	, m_parent(parent)
{
	InitUndoAction();
	InitRedoAction();

	CreateView();
}

HistoryMenuController::~HistoryMenuController()
{
	delete m_view;
	delete m_undoAction;
	delete m_redoAction;
}


void HistoryMenuController::CreateView()
{
	m_view = new QMenu(tr("&History"), m_parent);
	m_view->addAction(m_undoAction);
	m_view->addAction(m_redoAction);
}

QMenu* HistoryMenuController::View()
{
	return m_view;
}

void HistoryMenuController::UndoHandler()
{
	m_editorController->Undo();
}

void HistoryMenuController::RedoHandler()
{
	m_editorController->Redo();
}


void HistoryMenuController::InitUndoAction()
{
	m_undoAction = new QAction(tr("&Undo"), this);
	m_undoAction->setShortcut(tr("Ctrl+Z"));
	connect(m_undoAction, SIGNAL(triggered()), this, SLOT(UndoHandler()));
}

void HistoryMenuController::InitRedoAction()
{
	m_redoAction = new QAction(tr("&Redo"), this);
	m_redoAction->setShortcut(tr("Ctrl+Y"));
	connect(m_redoAction, SIGNAL(triggered()), this, SLOT(RedoHandler()));
}
