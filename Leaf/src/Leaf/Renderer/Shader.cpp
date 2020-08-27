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

	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& pixelSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			LF_CORE_ASSERT(false, "No Render API is not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLShader>(name,vertexSrc,pixelSrc);
		}
		return nullptr;
	}

	ShaderManager::ShaderManager()
	{
		m_Shaders.reserve(2);
	}

	ShaderManager::~ShaderManager()
	{
	}
	
	void ShaderManager::Add(const Ref<Shader>& shader)
	{
		Add(shader->GetName(), shader);
	}
	
	void ShaderManager::Add(const std::string& name, const Ref<Shader>& shader)
	{
		LF_CORE_ASSERT(m_Shaders.find(name) == m_Shaders.end(), "Shader [{0}] already loaded!", name);

		m_Shaders[name] = shader;
	}
	
	Ref<Shader> ShaderManager::Load(const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(shader->GetName(), shader);
		return shader;
	}
	
	Ref<Shader> ShaderManager::Load(const std::string& name, const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(name, shader);
		return shader;
	}
	Ref<Shader> ShaderManager::Get(const std::string& name)
	{
		LF_CORE_ASSERT(m_Shaders.find(name) != m_Shaders.end(), "Shader [{0}] not loaded!",name);
		return m_Shaders[name];
	}
}