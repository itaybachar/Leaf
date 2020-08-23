#pragma once
#include "Leaf/Renderer/Buffer.h"

namespace Leaf {
	
	class OpenGLVertexBuffer : public VertexBuffer {
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer() override;

		virtual void Bind() const override;
		virtual void Unbind() const override;

		inline virtual void SetLayout(BufferLayout& layout) override {
			m_Layout = layout;
		};
		inline virtual const BufferLayout& GetLayout() const {
			return m_Layout;
		}

	private:
		uint32_t m_ID;
		BufferLayout m_Layout;
	};

	class OpenGLIndexBuffer : public IndexBuffer {
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer() override;

		virtual void Bind() const override;
		virtual void Unbind() const override;

		inline virtual uint32_t GetCount() const override {
			return m_Count;
		}
	private:
		uint32_t m_ID;
		uint32_t m_Count;
	};
}