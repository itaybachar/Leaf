#include "lfpch.h"
#include "Leaf/Renderer/Renderer.h"

namespace Leaf {

	Renderer::SceneData* Renderer::m_Data = new Renderer::SceneData;

	void Renderer::BeginScene(Camera& camera)
	{
		m_Data->ViewProjection = camera.GetViewProjection();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<Shader> shader, const std::shared_ptr<VertexArray>& vertexArray)
	{
		shader->Bind();
		shader->UploadUniformMat4("u_ViewProjection", m_Data->ViewProjection);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}