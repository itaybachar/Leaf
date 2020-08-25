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

		LF_CORE_INFO("OpenGL Info:");
		LF_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		LF_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		LF_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
		
		LF_CORE_ASSERT(GLVersion.major > 4 || (GLVersion.major == 4 && GLVersion.minor >= 5), "Leaf requires at least OpenGL version 4.5!");
	}
	void OpenGLContext::SwapBuffers() {
		glfwSwapBuffers(m_WindowHandle);
	}
}