#pragma once
#include <memory>
#include <QWidget>
#include "Image.h"

class IEditorView : public QWidget
{
public:
	IEditorView(QWidget* parent)
		: QWidget(parent)
	{
	}

	virtual void SetImage(std::shared_ptr<QImage> image) = 0;
};