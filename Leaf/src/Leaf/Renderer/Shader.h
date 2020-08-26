#pragma once

namespace Leaf {

	enum class ShaderDataType {
		None = 0,
		Float, Float2, Float3, Float4,
		Int, Int2, Int3, Int4,
		Mat3, Mat4,
		Bool
	};

	class Shader {
	public:
		virtual ~Shader() = default;
		
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
	public:
		static Ref<Shader> Create(const std::string& filepath);
		static Ref<Shader> Create(const std::string& vertexSrc, const std::string& pixelSrc);
	};
}