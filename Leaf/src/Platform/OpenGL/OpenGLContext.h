#pragma once
#include "Leaf/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Leaf {
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* window);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};

}
