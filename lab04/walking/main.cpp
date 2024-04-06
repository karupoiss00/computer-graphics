#include "pch.h"
#include "GLFWInitializer.h"
#include "ImguiInitializer.h"
#include "Window.h"

int main()
{
	GLFWInitializer initGLFW;
	ImguiInitializer initImgui;
	Window window { 1280, 720, "walking" };
	window.Run();
}