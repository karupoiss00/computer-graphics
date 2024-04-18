#include "GdiPlusInitializer.h"

GdiPlusInitializer::GdiPlusInitializer()
{
	Gdiplus::GdiplusStartupInput input;
	Gdiplus::GdiplusStartupOutput output;

	if (Gdiplus::GdiplusStartup(&m_token, &input, &output) != Gdiplus::Ok)
	{
		throw std::runtime_error("Failed to initialize GDI+");
	}
}

GdiPlusInitializer::~GdiPlusInitializer()
{
	Gdiplus::GdiplusShutdown(m_token);
}