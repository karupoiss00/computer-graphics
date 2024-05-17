#include <iostream>
#include "pch.h"
#include "GLEWInitializer.h"

GLEWInitializer::GLEWInitializer()
{
	auto code = glewInit();
	if (code != GLEW_OK)
	{
		std::cout << "Error: " << glewGetErrorString(code) << std::endl;
		throw std::runtime_error("Failed to initialize GLEW");
	}


	if (!GLEW_EXT_framebuffer_object)
	{
		throw std::runtime_error("GL_EXT_framebuffer_object extension is not available");
	}

	if (!GLEW_ARB_shader_objects)
	{
		throw std::runtime_error("GLEW_ARB_shader_objects extension is not available");
	}
}