#pragma once
#include "Leaf/Renderer/Shader.h"

namespace Leaf {
	class OpenGLShader : public Shader {
	public:
		OpenGLShader(const std::string& vertexSrc, const std::string& pixelSrc);
		virtual ~OpenGLShader();
		
		virtual void Bind() const;
		virtual void Unbind() const;

		inline uint32_t GetProgram() const { return m_ID; }
	private:
		uint32_t m_ID;
	};
}