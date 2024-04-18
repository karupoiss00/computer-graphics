#pragma once
#include "pch.h"

class GdiPlusInitializer
{
public:
	GdiPlusInitializer();

	~GdiPlusInitializer();

private:
	ULONG_PTR m_token;
};