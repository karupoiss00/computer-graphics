#pragma once
#include <QImage>
#include "IMemento.h"
#include "Image.h"

struct EditorData
{
	QImage image;
	bool hasUnsavedChanges;
};

class EditorMemento : public IMemento<EditorData>
{
public:
	EditorMemento(EditorData data)
		: m_data(data)
	{
	}

	EditorData State() const 
	{
		return m_data;
	}

private: 
	EditorData m_data;
};