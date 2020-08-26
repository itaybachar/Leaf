#include "lfpch.h"
#include "Leaf/Renderer/Shader.h"
#include "Leaf/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Leaf {

	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			LF_CORE_ASSERT(false, "No Render API is not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLShader>(filepath);
		}
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& vertexSrc, const std::string& pixelSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			LF_CORE_ASSERT(false, "No Render API is not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLShader>(vertexSrc,pixelSrc);
		}
		return nullptr;
	}
}