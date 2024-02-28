#pragma once
#include <QColor>
#include <QPoint>
#include "Document.h"

class EditorState
{
public:
	EditorState(Document* document);

	void SetPenColor(QColor color);
	void SetPenSize(int size);

	[[nodiscard]] QColor GetPenColor() const;
	[[nodiscard]] int GetPenSize() const;

private:
	Document* m_document;

	QColor m_penColor;

	int m_penSize;
};