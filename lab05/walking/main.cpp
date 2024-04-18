#include "pch.h"
#include "GLFWInitializer.h"
#include "ImguiInitializer.h"
#include "GdiPlusInitializer.h"
#include "Window.h"

int main()
{
	GLFWInitializer initGLFW;
	ImguiInitializer initImgui;
	GdiPlusInitializer initGdiPlus;
	Window window { 1280, 720, "walking" };
	window.Run();
}