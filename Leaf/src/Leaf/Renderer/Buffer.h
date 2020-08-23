#pragma once

#include "Leaf/Renderer/Shader.h"

namespace Leaf {

	static uint32_t ShaderDataTypeSize(ShaderDataType type) {
		switch (type)
		{
			case Leaf::ShaderDataType::Float:   return 4;
			case Leaf::ShaderDataType::Float2:	return 4 * 2;
			case Leaf::ShaderDataType::Float3:	return 4 * 3;
			case Leaf::ShaderDataType::Float4:	return 4 * 4;
			case Leaf::ShaderDataType::Int:		return 4;
			case Leaf::ShaderDataType::Int2:	return 4 * 2;
			case Leaf::ShaderDataType::Int3:	return 4 * 3;
			case Leaf::ShaderDataType::Int4:	return 4 * 4;
			case Leaf::ShaderDataType::Mat3:	return 4 * 3 * 3;
			case Leaf::ShaderDataType::Mat4:	return 4 * 4 * 4;
			case Leaf::ShaderDataType::Bool:	return 1;
		}

		LF_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	struct LayoutElement {
		ShaderDataType Type;
		std::string Name;
		uint32_t Size;
		uint32_t Offset;
		bool Normalized;

		LayoutElement() {};

		LayoutElement(ShaderDataType type, const std::string& name, bool normalized = false)
			: Type(type), Name(name), Size(ShaderDataTypeSize(type)), Normalized(normalized) {}

		uint32_t GetCount() const {
			switch (Type)
			{
			case Leaf::ShaderDataType::Float:   return 1;
			case Leaf::ShaderDataType::Float2:	return 2;
			case Leaf::ShaderDataType::Float3:	return 3;
			case Leaf::ShaderDataType::Float4:	return 4;
			case Leaf::ShaderDataType::Int:		return 1;
			case Leaf::ShaderDataType::Int2:	return 2;
			case Leaf::ShaderDataType::Int3:	return 3;
			case Leaf::ShaderDataType::Int4:	return 4;
			case Leaf::ShaderDataType::Mat3:	return 3 * 3;
			case Leaf::ShaderDataType::Mat4:	return 4 * 4;
			case Leaf::ShaderDataType::Bool:	return 1;
			}

			LF_CORE_ASSERT(false, "Unknown ShaderDataType!");
			return 0;
		}
	};

	class BufferLayout {
	public:
		BufferLayout() {}
		BufferLayout(const std::initializer_list<LayoutElement>& elements)
			: m_Elements(elements)
		{
			CalculateStrideAndOffset();
		}

		inline const std::vector<LayoutElement>& GetElemets() const { return m_Elements; }
		inline uint32_t GetStride() const { return m_Stride; }

		//Allows foreach
		inline std::vector<LayoutElement>::iterator begin() { return m_Elements.begin(); }
		inline std::vector<LayoutElement>::iterator end() { return m_Elements.end(); }

		inline std::vector<LayoutElement>::const_iterator begin() const { return m_Elements.begin(); }
		inline std::vector<LayoutElement>::const_iterator end() const { return m_Elements.end(); }

	private:
		void CalculateStrideAndOffset() {
			uint32_t offset = 0;
			m_Stride = 0;
			for (auto& elem : m_Elements)
			{
				elem.Offset = offset;
				offset += elem.Size;
				m_Stride += elem.Size;
			}
		}

	private:
		std::vector<LayoutElement> m_Elements;
		uint32_t m_Stride;
	};

	class VertexBuffer {
	public:
		virtual ~VertexBuffer() {};
		
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		
		virtual void SetLayout(BufferLayout& layout) = 0;
		virtual const BufferLayout& GetLayout() const = 0;

	public:
		static VertexBuffer* Create(float* vertices, uint32_t size);
	};

	class IndexBuffer {
	public:
		virtual ~IndexBuffer() {};

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetCount() const = 0;

	public:
		static IndexBuffer* Create(uint32_t* indices, uint32_t count);
	};
}