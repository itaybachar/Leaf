#pragma once
#include "Leaf/Renderer/Shader.h"

#include <glm/glm.hpp>

//TODO: TEMPORARY
typedef unsigned int GLenum;

namespace Leaf {
	class OpenGLShader : public Shader {
	public:
		OpenGLShader(const std::string& filepath);
		OpenGLShader(const std::string& vertexSrc, const std::string& pixelSrc);

		virtual ~OpenGLShader();
		
		virtual void Bind() const override;
		virtual void Unbind() const override;

		void UploadUniformInt(const std::string& name, int value) const;

		void UploadUniformFloat(const std::string& name, float value) const;
		void UploadUniformFloat2(const std::string& name, const glm::vec2& values) const;
		void UploadUniformFloat3(const std::string& name, const glm::vec3& values) const;
		void UploadUniformFloat4(const std::string& name, const glm::vec4& values) const;

		void UploadUniformMat2(const std::string& name, const glm::mat2& matrix) const;
		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix) const;
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) const;

		inline uint32_t GetProgram() const { return m_ID; }

	private:
		std::string ReadFile(const std::string& filepath);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
		void Compile(const std::unordered_map<GLenum, std::string>& sources);

	private:
		uint32_t m_ID;
	};
}