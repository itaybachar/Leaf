#include "lfpch.h"
#include "Platform/OpenGL/OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Leaf {

	OpenGLContext::OpenGLContext(GLFWwindow* window)
		: m_WindowHandle(window) 
	{
		LF_CORE_ASSERT(window, "Window handle is null!");
	}

	void OpenGLContext::Init() {
		glfwMakeContextCurrent(m_WindowHandle);

		int res = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		LF_ASSERT(res, "Failed to load GL Loader! (Glad)");
	}
	void OpenGLContext::SwapBuffers() {
		glfwSwapBuffers(m_WindowHandle);
	}
}