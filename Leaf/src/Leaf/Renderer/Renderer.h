#pragma once
#include "Leaf/Renderer/RenderCommand.h"
#include "Leaf/Renderer/Camera.h"

namespace Leaf {

	class Renderer {
	public:
		static void BeginScene(Camera& camera);
		static void EndScene();

		static void Submit(const std::shared_ptr<Shader> shader, const std::shared_ptr<VertexArray>& vertexArray);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData {
			glm::mat4 ViewProjection;
		};

		static SceneData* m_Data;
	};
}