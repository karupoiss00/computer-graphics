#pragma once
#include <QImage>
#include "Image.h"

Image createImageFromQImage(QImage const& img);
QImage createQImageFromImage(Image const& img);