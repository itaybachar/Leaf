#pragma once
#include "Leaf/Renderer/RenderCommand.h"
#include "Leaf/Renderer/Camera.h"

namespace Leaf {

	class Renderer {
	public:

		static void Init();

		static void BeginScene(Camera& camera);
		static void EndScene();

		static void Submit(const Ref<Shader> shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData {
			glm::mat4 ViewProjection;
		};

		static SceneData* m_Data;
	};
}