#pragma once
#include "Leaf/Renderer/RendererAPI.h"

namespace Leaf {
	class OpenGLRendererAPI : public RendererAPI {
	public:
		OpenGLRendererAPI();
		virtual ~OpenGLRendererAPI() override;

		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;
		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
	};
}