#pragma once
#include "Image.h"

class Document 
{
public:
	Document();

	void SetImage(Image image);
	void SaveChanges();
	
	bool HasUnsavedChanges();

	[[nodiscard]] Image const& GetImage() const;
	[[nodiscard]] WriteProxy<Image> GetEditableImage();
	[[nodiscard]] WriteProxy<Image> operator--(int);

private:
	Image m_image;
	bool m_hasUnsavedChanges;
};