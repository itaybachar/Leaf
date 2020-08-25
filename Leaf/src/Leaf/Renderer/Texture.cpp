#include "lfpch.h"

#include "Leaf/Renderer/Texture.h"
#include "Leaf/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLTexture.h"

namespace Leaf {
	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			LF_CORE_ASSERT(false, "No Render API is not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLTexture2D>(path);
		}
		return nullptr;
	}
}