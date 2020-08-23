#include "lfpch.h"
#include "Leaf/Renderer/RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Leaf {
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();
}