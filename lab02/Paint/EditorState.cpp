#include "EditorState.h"

const int DEFAULT_PEN_SIZE = 3;
const QColor DEFAULT_PEN_COLOR = QColor::fromRgb(255,255,255);

EditorState::EditorState(Document* document)
	: m_document(document) 
	, m_penSize(DEFAULT_PEN_SIZE)
	, m_penColor(DEFAULT_PEN_COLOR)
{

}

void EditorState::SetPenColor(QColor color)
{
	m_penColor = color;
}

void EditorState::SetPenSize(int size)
{
	m_penSize = size;
}

[[nodiscard]] QColor EditorState::GetPenColor() const
{
	return m_penColor;
}

[[nodiscard]] int EditorState::GetPenSize() const
{
	return m_penSize;
}
