#include "ToolsMenuController.h"
#include "EditorController.h"

ToolsMenuController::ToolsMenuController(QWidget* parent, EditorController* controller)
	: m_editorController(controller)
	, m_parent(parent)
{
	InitSetDrawColorAction();
	InitSetDrawSizeAction();
	InitSetPenToolAction();
	InitSetLineToolAction();
	InitSetEllipseToolAction();
	InitClearScreenAction();

	CreateView();
}

ToolsMenuController::~ToolsMenuController()
{
	delete m_toolsActionGroup;
	delete m_view;

	delete m_drawColorChangeAction;
	delete m_drawSizeChangeAction;

	delete m_setPenToolAction;
	delete m_setLineToolAction;
	delete m_setEllipseToolAction;

	delete m_clearScreenAction;
}

void ToolsMenuController::CreateView()
{
	m_view = new QMenu(tr("&Options"), m_parent);

	m_toolsActionGroup = new QActionGroup(m_view);
	m_toolsActionGroup->setExclusive(true);
	m_toolsActionGroup->addAction(m_setPenToolAction);
	m_toolsActionGroup->addAction(m_setLineToolAction);
	m_toolsActionGroup->addAction(m_setEllipseToolAction);
	m_setPenToolAction->setChecked(true);

	m_view->addAction(m_drawColorChangeAction);
	m_view->addAction(m_drawSizeChangeAction);
	m_view->addSeparator();
	m_view->addActions(m_toolsActionGroup->actions());
	m_view->addSeparator();
	m_view->addAction(m_clearScreenAction);
}

void ToolsMenuController::InitSetDrawColorAction()
{
	m_drawColorChangeAction = new QAction(tr("&Draw Color..."), this);
	connect(m_drawColorChangeAction, SIGNAL(triggered()), this, SLOT(DrawColorChangeHandler()));
}

void ToolsMenuController::DrawColorChangeHandler()
{
	auto drawingSettings = m_editorController->GetDrawingSettings();
	QColor newColor = QColorDialog::getColor(drawingSettings.color);

	if (!newColor.isValid())
	{
		return;
	}

	m_editorController->SetDrawingColor(newColor);
}


void ToolsMenuController::InitSetDrawSizeAction()
{
	m_drawSizeChangeAction = new QAction(tr("Draw &Size..."), this);
	connect(m_drawSizeChangeAction, SIGNAL(triggered()), this, SLOT(DrawSizeChangeHandler()));
}

void ToolsMenuController::DrawSizeChangeHandler()
{
	auto drawingSettings = m_editorController->GetDrawingSettings();
	bool ok;

	int newSize = QInputDialog::getInt(
		m_parent,
		tr("Size"),
		tr("Select draw size:"),
		drawingSettings.size,
		1, 50, 1,
		&ok);

	if (ok)
	{
		m_editorController->SetDrawingSize(newSize);
	}
}


void ToolsMenuController::InitSetPenToolAction()
{
	m_setPenToolAction = new QAction(tr("&Pen"), this);
	m_setPenToolAction->setCheckable(true);
	connect(m_setPenToolAction, SIGNAL(triggered()), this, SLOT(SetPenToolHandler()));
}

void ToolsMenuController::SetPenToolHandler()
{
	m_editorController->SetDrawingTool("pen");
}

void ToolsMenuController::InitSetLineToolAction()
{
	m_setLineToolAction = new QAction(tr("&Line"), this);
	m_setLineToolAction->setCheckable(true);
	connect(m_setLineToolAction, SIGNAL(triggered()), this, SLOT(SetLineToolHandler()));
}

void ToolsMenuController::SetLineToolHandler()
{
	m_editorController->SetDrawingTool("line");
}

void ToolsMenuController::InitSetEllipseToolAction()
{
	m_setEllipseToolAction = new QAction(tr("&Circle"), this);
	m_setEllipseToolAction->setCheckable(true);
	connect(m_setEllipseToolAction, SIGNAL(triggered()), this, SLOT(SetEllipseToolHandler()));
}

void ToolsMenuController::SetEllipseToolHandler()
{
	m_editorController->SetDrawingTool("circle");
}

void ToolsMenuController::InitClearScreenAction()
{
	m_clearScreenAction = new QAction(tr("&Clear Screen"), this);
	m_clearScreenAction->setShortcut(tr("Ctrl+L"));
	connect(m_clearScreenAction, SIGNAL(triggered()), this, SLOT(ClearImageHandler()));
}

void ToolsMenuController::ClearImageHandler()
{
	m_editorController->ClearImage();
}

QMenu* ToolsMenuController::View()
{
	return m_view;
}