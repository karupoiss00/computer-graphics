#pragma once
#include <QMenu>
#include "IEditor.h"

class QHistoryMenu : public QMenu
{
	Q_OBJECT
public:
	QHistoryMenu(IEditor* m_editor);

private slots:
	void UndoActionHandler();
	void RedoActionHandler();

private:
	QAction* m_undoAction;
	QAction* m_redoAction;
};