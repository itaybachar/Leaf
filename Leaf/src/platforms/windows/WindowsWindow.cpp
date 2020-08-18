#include "lfpch.h"
#include "WindowsWindow.h"
#include "Leaf/Logger.h"

#include "Leaf/Events/ApplicationEvent.h"
#include "Leaf/Events/MouseEvent.h"
#include "Leaf/Events/KeyEvent.h"

#include <GLFW/glfw3.h>

namespace Leaf {

	static bool s_GLFWInitialized = false;

	static void GLFWErrorCallback(int code, const char* msg)
	{
		LF_CORE_ERROR("GLFW Error ({0}): {1}", code, msg);
	}

	Window* Window::Create(const WindowProps& props) {
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}
	
	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::OnUpdate()
	{
		glClearColor(0.9f, 0.9f, 0.9f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(m_Window);
		glfwPollEvents();
	}
	
	void WindowsWindow::SetVSync(bool vsync)
	{
		if (vsync)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = vsync;
	}
	void WindowsWindow::Init(const WindowProps& props)
	{
		//Set the window Data from props
		m_Data.m_Title = props.m_Title;
		m_Data.m_Width = props.m_Width;
		m_Data.m_Height = props.m_Height;

		//Initialize GLFW if needed
		if (!s_GLFWInitialized) {
			bool res = glfwInit();

			LF_ASSERT(res, "Failed to initialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
			LF_CORE_INFO("GLFW Initialize!");
			s_GLFWInitialized = true;
		}

		//Create window
		m_Window = glfwCreateWindow(m_Data.m_Width, m_Data.m_Height, m_Data.m_Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);

		//Set Callbacks

		//Key
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int keycode, int scancode, int actions, int mods) {
			Data& data = *(Data*)glfwGetWindowUserPointer(window);

			switch (actions) {
			case GLFW_PRESS:
			{
				KeyPressEvent e(keycode, 0);
				data.callback(e);
				break;
			}
			case GLFW_RELEASE:
			{
				KeyReleaseEvent e(keycode);
				data.callback(e);
				break;
			}
			case GLFW_REPEAT:
			{
				KeyPressEvent e(keycode, 1);
				data.callback(e);
				break;
			}
			}
			});

		//Mouse
		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos) {
			Data& data = *(Data*)glfwGetWindowUserPointer(window);

			MouseMoveEvent e((float)xPos, (float)yPos);
			data.callback(e);
			});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int actions, int mods) {
			Data& data = *(Data*)glfwGetWindowUserPointer(window);

			switch (actions) {
			case GLFW_PRESS:
			{
				MouseButtonPressEvent e(button);
				data.callback(e);
				break;
			}
			case GLFW_RELEASE:
			{
				MouseButtonReleaseEvent e(button);
				data.callback(e);
				break;
			}
			}
			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset) {

			Data& data = *(Data*)glfwGetWindowUserPointer(window);

			MouseScrollEvent e((float)xOffset, (float)yOffset);
			data.callback(e);
			});

		//App
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
			Data& data = *(Data*)glfwGetWindowUserPointer(window);

			data.m_Width = width;
			data.m_Height = height;

			WindowResizeEvent e(width, height);
			data.callback(e);
			});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
			Data& data = *(Data*)glfwGetWindowUserPointer(window);

			WindowCloseEvent e;
			data.callback(e);
			});

		glfwSetWindowFocusCallback(m_Window, [](GLFWwindow* window, int focused) {
			Data& data = *(Data*)glfwGetWindowUserPointer(window);

			switch (focused) {
			case GLFW_TRUE:
			{
				WindowFocusEvent e;
				data.callback(e);
				break;
			}
			case GLFW_FALSE:
			{
				WindowLostFocusEvent e;
				data.callback(e);
				break;
			}
			}
			});

		//Turn on VSync by default
		SetVSync(true);
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}
}