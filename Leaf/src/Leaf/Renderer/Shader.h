#pragma once

#include <glm/glm.hpp>

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
		virtual ~Shader() {};
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) const = 0;
	public:
		static Shader* Create(const std::string& vertexSrc, const std::string& pixelSrc);
	};
}