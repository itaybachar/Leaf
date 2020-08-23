#pragma once

namespace Leaf {
	class Shader {
	public:
		Shader(const std::string& vertexSrc, const std::string& pixelSrc);
		~Shader();
		void Bind();
		void Unbind();

	private:
		uint32_t m_ProgramID;
	};
}