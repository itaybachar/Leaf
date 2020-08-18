#include "lfpch.h"
#include "WindowsWindow.h"
#include "Leaf/Logger.h"
#include "Leaf/Events/KeyEvent.h"

#include <GLFW/glfw3.h>

namespace Leaf {

	static bool s_GLFWInitialized = false;

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
			LF_CORE_INFO("GLFW Initialize!");
			s_GLFWInitialized = true;
		}

		//Create window
		m_Window = glfwCreateWindow(m_Data.m_Width, m_Data.m_Height, m_Data.m_Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);

		//Set Callbacks
		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos) {
			
			auto& data = *(Data*)glfwGetWindowUserPointer(window);
			//data.callback();
			LF_CORE_TRACE("{0}", Leaf::KeyPressEvent(1,2));
			});

		//Turn on VSync by default
		SetVSync(true);
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}
}