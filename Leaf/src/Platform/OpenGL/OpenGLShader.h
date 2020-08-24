#pragma once
#include "Leaf/Renderer/Shader.h"

namespace Leaf {
	class OpenGLShader : public Shader {
	public:
		OpenGLShader(const std::string& vertexSrc, const std::string& pixelSrc);
		virtual ~OpenGLShader();
		
		virtual void Bind() const;
		virtual void Unbind() const;

		virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) const;

		inline uint32_t GetProgram() const { return m_ID; }
	private:
		uint32_t m_ID;
	};
}