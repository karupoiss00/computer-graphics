#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>
#include "pch.h"
#include "Program.h"
#include "Renderable.h"
#include "ObjectWithShader.h"
#include "Shader.h"
#include "ShaderLoader.h"
#include "ShaderCompiler.h"
#include "ProgramLinker.h"
#include "Program.h"
#include "ProgramInfo.h"

template<GLenum SHADER_TYPE>
class ObjectWithShader : public IRenderable
{
public:
	ObjectWithShader(std::wstring shaderFileName)

		: m_shadersLoaded(false)
		, m_program()
		, m_shaderFileName(shaderFileName)
	{

	};

	void Render() const final
	{
		if (!m_shadersLoaded)
		{
			SetupShaders();
		}

		glUseProgram(m_program);

		RenderObject();

		glUseProgram(0);
	}

	void Reload() final
	{
		m_shadersLoaded = false;
		SetupShaders();
	}

protected:
	virtual void RenderObject() const = 0;
private:
	void SetupShaders() const
	{
		try
		{
			ShaderLoader loader;
			Shader vertexShader = loader.LoadShader(SHADER_TYPE, m_shaderFileName.c_str());

			ShaderCompiler compiler;

			compiler.CompileShader(vertexShader);

			m_program.Create();
			m_program.AttachShader(vertexShader);

			compiler.CheckStatus();

			ProgramLinker linker;

			linker.LinkProgram(m_program);
			linker.CheckStatus();

			ProgramInfo info(m_program);
			info.Print(std::cout);
		}
		catch (std::exception const& e)
		{
			std::cout << e.what() << std::endl;
		}

		m_shadersLoaded = true;
	}

	mutable Program m_program;
	mutable bool m_shadersLoaded;
	std::wstring m_shaderFileName;
};