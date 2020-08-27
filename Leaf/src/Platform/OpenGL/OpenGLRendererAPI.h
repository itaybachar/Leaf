#pragma once
#include "Leaf/Renderer/RendererAPI.h"

namespace Leaf {
	class OpenGLRendererAPI : public RendererAPI {
	public:
		OpenGLRendererAPI();
		virtual ~OpenGLRendererAPI() override;

		virtual void Init() override;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;
		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
	};
}