#include <QImage>
#include "LoadImageFromFile.h"

QImage LoadImageFromFile(QString fileName)
{
	QImage loadedImage;
	loadedImage.convertToFormat(QImage::Format_ARGB32);

	if (!loadedImage.load(fileName))
	{
		return QImage();
	}

	return loadedImage;
}