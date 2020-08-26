#include "lfpch.h"
#include "Leaf/Renderer/Buffer.h"
#include "Leaf/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"


namespace Leaf {

	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			LF_CORE_ASSERT(false, "No Render API is not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLVertexBuffer>(vertices, size);
		}
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			LF_CORE_ASSERT(false, "No Render API is not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLIndexBuffer>(indices, count);
		}
		return nullptr;
	}
}