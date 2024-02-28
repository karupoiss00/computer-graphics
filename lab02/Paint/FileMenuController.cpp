#include "FileMenuController.h"
#include "EditorController.h"
#include "QImageToImage.h"
#include "LoadImageFromFile.h"

FileMenuController::FileMenuController(QWidget* parent, EditorController* controller)
	: m_editorController(controller)
	, m_parent(parent)
{
	InitOpenAction();
	InitSaveActions();
	InitExitAction();

	CreateView();
}

FileMenuController::~FileMenuController()
{
	delete m_view;
	delete m_openFileAction;
	delete m_exitAction;

	for (auto action : m_saveAsActions)
	{
		delete action;
	}
}

void FileMenuController::InitOpenAction()
{
	m_openFileAction = new QAction(tr("&Open..."), this);
	m_openFileAction->setShortcuts(QKeySequence::Open);
	connect(m_openFileAction, SIGNAL(triggered()), this, SLOT(OpenFileHandler()));
}

void FileMenuController::InitSaveActions()
{
	for (auto& format : QImageWriter::supportedImageFormats())
	{
		QString text = tr("%1...").arg(QString(format).toUpper());
		QAction* action = new QAction(text, this);
		action->setData(format);

		connect(action, SIGNAL(triggered()), this, SLOT(SaveFileHandler()));
		connect(action, SIGNAL(triggered()), m_editorController, SLOT(SaveImageHandler()));

		m_saveAsActions.append(action);
	}
}

void FileMenuController::InitExitAction()
{
	m_exitAction = new QAction(tr("E&xit"), this);
	m_exitAction->setShortcuts(QKeySequence::Quit);

	connect(m_exitAction, SIGNAL(triggered()), this, SLOT(FileCloseHandler()));
}

void FileMenuController::CreateView()
{
	m_saveMenuView = new QMenu(tr("&Save As"), m_parent);
	for (auto& action : m_saveAsActions)
	{
		m_saveMenuView->addAction(action);
	}

	m_view = new QMenu(tr("&File"), m_parent);
	m_view->addAction(m_openFileAction);
	m_view->addMenu(m_saveMenuView);
	m_view->addSeparator();
	m_view->addAction(m_exitAction);
}

void FileMenuController::OpenFileHandler()
{
	emit FileOpenEvent();

	QString fileName = QFileDialog::getOpenFileName(m_parent, tr("Open File"), QDir::currentPath());

	if (fileName.isEmpty())
	{
		return;
	}

	auto loadedImage = LoadImageFromFile(fileName);

	m_editorController->SetImage(loadedImage);
}

void FileMenuController::SaveFileHandler()
{
	QAction* action = qobject_cast<QAction*>(sender());

	QByteArray fileFormat = action->data().toByteArray();

	emit FileSaveEvent(fileFormat);
}

void FileMenuController::FileCloseHandler()
{
	emit FileCloseEvent();
}

QMenu* FileMenuController::View()
{
	return m_view;
}