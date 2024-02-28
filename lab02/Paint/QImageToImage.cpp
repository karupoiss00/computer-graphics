#include <vector>
#include "QImageToImage.h"

using namespace std;

Image createImageFromQImage(QImage const& img)
{
	vector<vector<Color>> colors;
	
	for (int y = 0; y < img.height(); y++)
	{
		colors.push_back({});
		for (int x = 0; x < img.width(); x++)
		{
			colors[y].push_back(
				img.pixel(x, y)
			);
		}
	}

	return Image(colors);
}

QImage createQImageFromImage(Image const& img)
{
	
	auto size = img.GetSize();

	QImage image(size.width, size.height, QImage::Format::Format_RGB32);

	for (int y = 0; y < size.height; y++)
	{
		for (int x = 0; x < size.width; x++)
		{
			QColor color(img.GetPixel({ x, y }));
			image.setPixelColor(x, y, color);
		}
	}

	return image;
}