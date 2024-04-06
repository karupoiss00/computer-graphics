#include "pch.h"
#include "BaseWindow.h"

BaseWindow::BaseWindow(int w, int h, const char* title)
	: m_window{ MakeWindow(w, h, title) }
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
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();

		auto size = GetFramebufferSize();
		Draw(size.x, size.y);
		DrawGUI(size.x, size.y);

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glFinish();
		glfwSwapBuffers(m_window);
		glfwPollEvents();
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