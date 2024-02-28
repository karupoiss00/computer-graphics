#pragma once
#include <QAction>

class EditorController;

class FileMenuController : public QObject
{
	Q_OBJECT
public:
	FileMenuController(QWidget* parent, EditorController* controller);

	QMenu* View();

	~FileMenuController();

private slots:
	void OpenFileHandler();
	void SaveFileHandler();
	void FileCloseHandler();

signals:
	void FileOpenEvent();
	void FileSaveEvent(const QByteArray& fileFormat);
	void FileCloseEvent();

private:
	void InitOpenAction();
	void InitSaveActions();
	void InitExitAction();

	void CreateView();


	QMenu* m_view;
	QMenu* m_saveMenuView;

	QAction* m_openFileAction;
	QList<QAction*> m_saveAsActions;
	QAction* m_exitAction;

	EditorController* m_editorController;

	QWidget* m_parent;
};