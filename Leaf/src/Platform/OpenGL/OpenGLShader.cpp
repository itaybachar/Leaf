#include "lfpch.h"
#include "Platform/OpenGL/OpenGLShader.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>

namespace Leaf {

	static GLenum GetShaderTypeFromToken(const std::string& token)
	{
		if (token == "vertex")
			return GL_VERTEX_SHADER;
		if (token == "fragment" || token == "pixel")
			return GL_FRAGMENT_SHADER;

		LF_CORE_ASSERT(false, "Token is not supported! [{0}]", token);
		return 0;
	}

	OpenGLShader::OpenGLShader(const std::string& filepath)
	{
		std::string file = ReadFile(filepath);
		auto sources = PreProcess(file);
		Compile(sources);
	}

	OpenGLShader::OpenGLShader(const std::string& vertexSrc, const std::string& pixelSrc)
	{
		std::unordered_map<GLenum, std::string> sources;
		sources[GL_VERTEX_SHADER] = vertexSrc;
		sources[GL_FRAGMENT_SHADER] = pixelSrc;
		Compile(sources);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_ID);
	}

	std::string OpenGLShader::ReadFile(const std::string& filepath)
	{
		std::string source;

		std::ifstream file(filepath, std::ios::in, std::ios::binary);
		
		//TODO: Should Break
		LF_CORE_ASSERT(file, "Could not open file '{0'", filepath);

		file.seekg(0, std::ios::end);
		source.resize(file.tellg());
		file.seekg(0, std::ios::beg);
		file.read(&source[0], source.size());

		file.close();

		return source;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& source)
	{
		std::unordered_map<GLenum, std::string> sources;

		const char* token = "#type";
		size_t tokenLen = strlen(token);
		size_t pos = source.find(token, 0);

		while (pos != std::string::npos)
		{
			size_t eol = source.find_first_of("\r\n",pos);

			LF_CORE_ASSERT(eol != std::string::npos, "Shader: Syntax Error!");
			size_t begin = pos + tokenLen + 1;
			std::string type = source.substr(begin, eol - begin);
			
			LF_CORE_ASSERT(GetShaderTypeFromToken(type), "Invalid Shader Type Specified. [{0}]", type);

			size_t nextLinePos =source.find_first_not_of("\r\n", eol);
			pos = source.find(token,nextLinePos);
			sources[GetShaderTypeFromToken(type)] = source.substr(nextLinePos, pos - (nextLinePos == std::string::npos? source.size() -1 : nextLinePos));
		}
		return sources;
	}

	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& sources)
	{
		//Cache shader ids
		std::vector<GLuint> shaderIds(sources.size());

		uint32_t program = glCreateProgram();
		//Compile Sources
		for (auto kv : sources)
		{
			GLuint shader = glCreateShader(kv.first);

			const std::string& source = kv.second;
			const GLchar* sourceCStr = source.c_str();
			glShaderSource(shader, 1, &sourceCStr, 0);

			// Compile the vertex shader
			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				// The maxLength includes the NULL character
				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				// We don't need the shader anymore.
				glDeleteShader(shader);

				// Use the infoLog as you see fit.
				LF_CORE_ERROR("{0}", infoLog.data());
				LF_CORE_ASSERT(false, "Vertex shader could not compile!");

				return;
			}
			glAttachShader(program, shader);
			
			//Save Shader for later
			shaderIds.push_back(shader);
		}

		// Link our program
		glLinkProgram(program);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);

			// Don't leak shaders either.
			for (GLuint shader : shaderIds)
				glDeleteShader(shader);

			return;
		}

		// Don't leak shaders either.
		for (GLuint shader : shaderIds)
			glDetachShader(program,shader);
		
		//Save the program id
		m_ID = program;
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_ID);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::UploadUniformInt(const std::string& name, int value) const
	{
		GLint location = glGetUniformLocation(m_ID, name.c_str());
		glUniform1i(location, value);
	}

	void OpenGLShader::UploadUniformFloat(const std::string& name, float value) const
	{
		GLint location = glGetUniformLocation(m_ID, name.c_str());
		glUniform1f(location, value);
	}

	void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& values) const
	{
		GLint location = glGetUniformLocation(m_ID, name.c_str());
		glUniform2fv(location, 1, glm::value_ptr(values));
	}

	void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& values) const
	{
		GLint location = glGetUniformLocation(m_ID, name.c_str());
		glUniform3fv(location, 1, glm::value_ptr(values));
	}

	void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& values) const
	{
		GLint location = glGetUniformLocation(m_ID, name.c_str());
		glUniform4fv(location, 1,glm::value_ptr(values));
	}

	void OpenGLShader::UploadUniformMat2(const std::string& name, const glm::mat2& matrix) const
	{
		GLint location = glGetUniformLocation(m_ID, name.c_str());
		glUniformMatrix2fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix) const
	{
		GLint location = glGetUniformLocation(m_ID, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix) const
	{
		GLint location = glGetUniformLocation(m_ID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}
}