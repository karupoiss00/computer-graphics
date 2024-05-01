#include "pch.h"
#include "GLFWInitializer.h"
#include "GLEWInitializer.h"
#include "ImguiInitializer.h"
#include "GdiPlusInitializer.h"
#include "Window.h"

GLFWInitializer initGLFW;
ImguiInitializer initImgui;
GdiPlusInitializer initGdiPlus;
Window window{ 1280, 720, "walking" };
GLEWInitializer initGLEW;

int main()
{
	window.Run();
}