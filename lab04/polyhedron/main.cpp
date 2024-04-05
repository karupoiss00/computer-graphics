#include "pch.h"
#include "GLFWInitializer.h"
#include "ImguiInitializer.h"
#include "Window.h"

int main()
{
	GLFWInitializer initGLFW;
	ImguiInitializer initImgui;
	Window window { 800, 600, "3D Cube" };
	window.Run();
}