#include "lfpch.h"
#include "Leaf/Renderer/VertexArray.h"
#include "Leaf/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Leaf {
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::None:
			LF_CORE_ASSERT(false, "No Render API is not supported!");
			return nullptr;
		case RenderAPI::OpenGL:
			return new OpenGLVertexArray();
		}
		return nullptr;
	}
}