#include "pch.h"
#include "BaseWindow.h"

BaseWindow::BaseWindow(int w, int h, const char* title)
	: m_window{ MakeWindow(w, h, title) }
	, m_lastTime(glfwGetTime())
	, m_nowTime(glfwGetTime())
{
	if (!m_window)
	{
		throw std::runtime_error("Failed to create window");
	}

	glfwSetWindowUserPointer(m_window, this);

	glfwSetWindowSizeCallback(m_window,
		[](GLFWwindow* window, int width, int height) {
			GetBaseWindow(window)->OnResize(width, height);
		});

	glfwSetMouseButtonCallback(m_window,
		[](GLFWwindow* window, int button, int action, int mods) {
			GetBaseWindow(window)->OnMouseButton(button, action, mods);
		});

	glfwSetCursorPosCallback(m_window,
		[](GLFWwindow* window, double x, double y) {
			GetBaseWindow(window)->OnMouseMove(x, y);
		});
	glfwSetKeyCallback(m_window,
		[](GLFWwindow* window, int key, int scancode, int action, int mods) {
			if (action == GLFW_PRESS)
			{
				GetBaseWindow(window)->OnKeyDown(key, scancode, mods);
			}

			if (action == GLFW_REPEAT)
			{
				GetBaseWindow(window)->OnKeyRepeat(key, scancode, mods);
			}

			if (action == GLFW_RELEASE)
			{
				GetBaseWindow(window)->OnKeyUp(key, scancode, mods);
			}
		});
}

BaseWindow::~BaseWindow()
{
	glfwDestroyWindow(m_window);
}

glm::ivec2 BaseWindow::GetFramebufferSize() const
{
	int w, h;
	glfwGetFramebufferSize(m_window, &w, &h);
	return { w, h };
}

void BaseWindow::Run()
{
	glfwMakeContextCurrent(m_window);
	ImGui_ImplGlfw_InitForOpenGL(m_window, true);
	ImGui_ImplOpenGL3_Init();

	OnRunStart();

	{
		auto size = GetFramebufferSize();
		OnResize(size.x, size.y);
	}

	while (!glfwWindowShouldClose(m_window))
	{
		m_nowTime = glfwGetTime();
		auto size = GetFramebufferSize();

		Draw(size.x, size.y);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		DrawGUI(size.x, size.y);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glFinish();
		glfwSwapBuffers(m_window);
		glfwPollEvents();
		m_lastTime = m_nowTime;
	}
	OnRunEnd();
}

glm::dvec2 BaseWindow::GetCursorPos() const
{
	double x, y;
	glfwGetCursorPos(m_window, &x, &y);
	return { x, y };
}

BaseWindow* BaseWindow::GetBaseWindow(GLFWwindow* window)
{
	return reinterpret_cast<BaseWindow*>(glfwGetWindowUserPointer(window));
}

GLFWwindow* BaseWindow::MakeWindow(int w, int h, const char* title)
{
	glfwWindowHint(GLFW_DEPTH_BITS, 24);
	return glfwCreateWindow(w, h, title, nullptr, nullptr);
}

void BaseWindow::ShowCursor(bool show)
{
	glfwSetInputMode(
		m_window, 
		GLFW_CURSOR,
		show
			? GLFW_CURSOR_NORMAL 
			: GLFW_CURSOR_DISABLED
	);
}

double BaseWindow::GetEllapsedTime()
{
	return m_nowTime - m_lastTime;
}