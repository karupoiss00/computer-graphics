#include <QtWidgets>

#include "Paint.h"
#include "Image.h"
#include "Editor.h"
#include "EditorView.h"
#include "EditorController.h"
#include "LoadImageFromFile.h"
#include "QImageToImage.h"

const QByteArray DEFAULT_SAVE_FORMAT = "png";

Paint::Paint()
{
	m_image = std::make_shared<QImage>(800, 800, QImage::Format_ARGB32);
	m_image->fill(0xFFFFFFFF);
	m_editorView = new EditorView(this, m_image);
	m_drawingStrategyFactory = DrawingStrategyFactory(m_image, m_editorView);
	m_editor = new Editor(m_image, m_drawingStrategyFactory);
	m_editorController = new EditorController(m_editorView, m_editor);

	setCentralWidget(m_editorView);
	CreateUI();

	setWindowTitle(tr("Paint"));

	auto size = m_image->size();
	resize(size.width(), size.height());
}

Paint::~Paint()
{
	delete m_editorController;
	delete m_editorView;
	delete m_editor;

	delete m_fileMenuController;
	delete m_toolsMenuController;
	delete m_historyMenuController;
}

void Paint::closeEvent(QCloseEvent* event)
{
	if (HasUnsavedChanges().has_value())
	{
		event->accept();
		return;
	}

	event->ignore();
}


void Paint::OpenFileHandler()
{
	HasUnsavedChanges();
}

void Paint::SaveFileHandler(const QByteArray& fileFormat)
{
	m_editorController->SaveImage();
	SaveFile(fileFormat);
}


void Paint::CreateUI()
{
	m_fileMenuController = new FileMenuController(this, m_editorController);
	connect(m_fileMenuController, &FileMenuController::FileOpenEvent, this, &Paint::OpenFileHandler);
	connect(m_fileMenuController, &FileMenuController::FileSaveEvent, this, &Paint::SaveFileHandler);
	connect(m_fileMenuController, &FileMenuController::FileCloseEvent, this, &Paint::close);

	m_toolsMenuController = new ToolsMenuController(this, m_editorController);

	m_historyMenuController = new HistoryMenuController(this, m_editorController);

	menuBar()->addMenu(m_fileMenuController->View());
	menuBar()->addMenu(m_toolsMenuController->View());
	menuBar()->addMenu(m_historyMenuController->View());
}

std::optional<bool> Paint::HasUnsavedChanges()
{
	if (!m_editor->HasUnsavedChanges())
	{
		return false;
	}

	QMessageBox::StandardButton ret;

	ret = QMessageBox::warning(this, tr("Paint"),
		tr("The image has been modified.\n"
		   "Do you want to save your changes?"),
		QMessageBox::Save | QMessageBox::Discard
			| QMessageBox::Cancel);

	if (ret == QMessageBox::Save)
	{
		SaveFile(DEFAULT_SAVE_FORMAT);

		return false;
	}

	if (ret == QMessageBox::Cancel)
	{
		return std::nullopt;
	}

	return true;
}

bool Paint::SaveFile(const QByteArray& fileFormat)
{
	QString initialPath = QDir::currentPath() + "/untitled." + fileFormat;

	QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
		initialPath,
		tr("%1 Files (*.%2);;All Files (*)")
			.arg(QString::fromLatin1(fileFormat.toUpper()))
			.arg(QString::fromLatin1(fileFormat)));

	if (fileName.isEmpty())
	{
		return false;
	}

	auto image = m_editorController->GetImage();

	if (image.save(fileName, fileFormat))
	{
		return true;
	}

	return false;
}
