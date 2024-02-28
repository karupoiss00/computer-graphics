#include <cassert>
#include <cstdlib>
#include <QDebug>
#include "Image.h"
#include "Geometry.h"
#include "Drawer.h"

namespace
{

int Sign(int value)
{
	return (0 < value) - (value < 0);
}

void DrawPoint(QImage& image, Point to, int radius, Color color)
{
	if (radius == 0)
	{
		image.setPixel(QPoint(to.x, to.y), color);
		return;
	}

	for (int y = to.y - radius; y < to.y + radius; y++)
	{
		for (int x = to.x - radius; x < to.x + radius; x++)
		{
			image.setPixel(QPoint(x, y), color);
		}
	}
}

void DrawSteepLine(QImage& image, Point from, Point to, Color color, int width)
{
	const int deltaX = std::abs(to.x - from.x);
	const int deltaY = std::abs(to.y - from.y);

	assert(deltaY >= deltaX);

	if (from.y > to.y)
	{
		std::swap(from, to);
	}

	const int stepX = Sign(to.x - from.x);
	const int errorThreshold = deltaY + 1; 
	const int deltaErr = deltaX + 1; 

	int error = deltaErr / 2;

	for (Point p = from; p.y <= to.y; ++p.y)
	{
		FillCircle(image, p, width / 2, color);

		assert((p.y != to.y) || (p.x == to.x));

		error += deltaErr;

		if (error >= errorThreshold)
		{
			p.x += stepX;
			error -= errorThreshold;
		}
	}
}

void DrawSlopeLine(QImage& image, Point from, Point to, Color color, int width)
{
	const int deltaX = std::abs(to.x - from.x);
	const int deltaY = std::abs(to.y - from.y);

	assert(deltaX >= deltaY);

	if (from.x > to.x)
	{
		std::swap(from, to);
	}

	const int stepY = Sign(to.y - from.y);
	const int errorThreshold = deltaX + 1;
	const int deltaErr = deltaY + 1;

	int error = deltaErr / 2;

	for (Point p = from; p.x <= to.x; ++p.x)
	{
		FillCircle(image, p, width / 2, color);
		assert((p.x != to.x) || (p.y == to.y));

		error += deltaErr;

		if (error >= errorThreshold)
		{
			p.y += stepY;
			error -= errorThreshold;
		}
	}
}

} // namespace

void DrawLine(QImage& image, Point from, Point to, Color color, int width)
{
	const int deltaX = std::abs(to.x - from.x);
	const int deltaY = std::abs(to.y - from.y);

	if (deltaY > deltaX)
	{
		DrawSteepLine(image, from, to, color, width);
	}
	else
	{
		DrawSlopeLine(image, from, to, color, width);
	}
}

void DrawCircle(QImage& image, Point center, int radius, Color color, int lineWidth)
{
	int x = radius;
	int y = 0;
	int radiusError = 1 - x;

	while (x >= y)
	{
		int pointRadius = lineWidth / 2;
		FillCircle(image, { center.x + x, center.y - y }, pointRadius, color);
		FillCircle(image, { center.x + x, center.y + y }, pointRadius, color);
		FillCircle(image, { center.x - x, center.y - y }, pointRadius, color);
		FillCircle(image, { center.x - x, center.y + y }, pointRadius, color);
		FillCircle(image, { center.x + y, center.y - x }, pointRadius, color);
		FillCircle(image, { center.x + y, center.y + x }, pointRadius, color);
		FillCircle(image, { center.x - y, center.y - x }, pointRadius, color);
		FillCircle(image, { center.x - y, center.y + x }, pointRadius, color);

		y++;

		if (radiusError < 0)
		{
			radiusError += 2 * y + 1;
		}
		else
		{
			x--;
			radiusError += 2 * (y - x + 1);
		}
	}
}

void FillCircle(QImage& image, Point center, int radius, Color color)
{
	int x = radius;
	int y = 0;
	int radiusError = 1 - x;

	while (x >= y)
	{
		for (int i = center.x - x; i <= center.x + x; ++i)
		{
			image.setPixel(QPoint{ i, center.y - y }, color);
			image.setPixel(QPoint{ i, center.y + y }, color);
		}

		for (int i = center.x - y; i <= center.x + y; ++i)
		{
			image.setPixel(QPoint{ i, center.y - x }, color);
			image.setPixel(QPoint{ i, center.y + x }, color);
		}

		y++;

		if (radiusError < 0)
		{
			radiusError += 2 * y + 1;
		}
		else
		{
			x--;
			radiusError += 2 * (y - x + 1);
		}
	}
}