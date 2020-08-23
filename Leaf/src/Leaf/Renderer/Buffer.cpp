#include "lfpch.h"
#include "Leaf/Renderer/Buffer.h"
#include "Leaf/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"


namespace Leaf {

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			LF_CORE_ASSERT(false, "No Render API is not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLVertexBuffer(vertices, size);
		}
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			LF_CORE_ASSERT(false, "No Render API is not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLIndexBuffer(indices, count);
		}
		return nullptr;
	}
}