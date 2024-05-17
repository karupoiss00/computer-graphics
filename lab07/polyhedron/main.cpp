#include "pch.h"
#include "GLFWInitializer.h"
#include "GLEWInitializer.h"
#include "ImguiInitializer.h"
#include "Window.h"

GLFWInitializer initGLFW;
ImguiInitializer initImgui;
Window window{ 1280, 720, "polyhedron" };
GLEWInitializer initGLEW;

int main()
{
	window.Run();
}