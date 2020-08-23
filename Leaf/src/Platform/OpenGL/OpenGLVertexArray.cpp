#include "lfpch.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Leaf {

	static GLenum ShaderDataType2APIType(ShaderDataType type) {
		switch (type)
		{
		case Leaf::ShaderDataType::Float:   return GL_FLOAT;
		case Leaf::ShaderDataType::Float2:	return GL_FLOAT;
		case Leaf::ShaderDataType::Float3:	return GL_FLOAT;
		case Leaf::ShaderDataType::Float4:	return GL_FLOAT;
		case Leaf::ShaderDataType::Int:		return GL_INT;
		case Leaf::ShaderDataType::Int2:	return GL_INT;
		case Leaf::ShaderDataType::Int3:	return GL_INT;
		case Leaf::ShaderDataType::Int4:	return GL_INT;
		case Leaf::ShaderDataType::Mat3:	return GL_FLOAT_MAT3;
		case Leaf::ShaderDataType::Mat4:	return GL_FLOAT_MAT4;
		case Leaf::ShaderDataType::Bool:	return GL_BOOL;
		}

		LF_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}


	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_ID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_ID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_ID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		glBindVertexArray(m_ID);
		vertexBuffer->Bind();

		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		
		LF_CORE_ASSERT(layout.GetElemets().size(), "Layout in VertexBuffer is not set!");
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.GetCount(),
				ShaderDataType2APIType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset);
			index++;
		}

		glBindVertexArray(0);

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_ID);
		indexBuffer->Bind();
		glBindVertexArray(0);
		
		m_IndexBuffer = indexBuffer;
	}
}