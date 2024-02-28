#include "Document.h"

Document::Document()
	: m_hasUnsavedChanges(false)
{}

[[nodiscard]] Image const& Document::GetImage() const
{

	return m_image;
}

void Document::SetImage(Image image)
{
	m_image = image;
	m_hasUnsavedChanges = true;
}

void Document::SaveChanges()
{
	m_hasUnsavedChanges = false;
}

bool Document::HasUnsavedChanges()
{
	return m_hasUnsavedChanges;
}

[[nodiscard]] WriteProxy<Image> Document::operator--(int)
{
	m_hasUnsavedChanges = true;
	return WriteProxy(&m_image);
}

[[nodiscard]] WriteProxy<Image> Document::GetEditableImage()
{
	m_hasUnsavedChanges = true;
	return WriteProxy(&m_image);
}