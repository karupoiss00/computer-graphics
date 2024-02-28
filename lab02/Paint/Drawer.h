#pragma once
#include <QImage>

void DrawLine(QImage& image, Point from, Point to, Color color, int width = 1);
void DrawCircle(QImage& image, Point center, int radius, Color color, int lineWidth = 1);
void FillCircle(QImage& image, Point center, int radius, Color color);