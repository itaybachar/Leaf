#pragma once

namespace Leaf {

	class Shader {
	public:
		virtual ~Shader() {};
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
	public:
		static Shader* Create(const std::string& vertexSrc, const std::string& pixelSrc);
	};
}