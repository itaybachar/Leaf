#pragma once
#include "Leaf/Renderer/Texture.h"

namespace Leaf {

	class OpenGLTexture2D : public Texture2D {
	public:
		OpenGLTexture2D(const std::string& path);

		virtual ~OpenGLTexture2D() override;

		inline virtual uint32_t GetWidth() const override { return m_Width; };
		inline virtual uint32_t GetHeight() const override { return m_Height; }

		virtual void Bind(uint32_t slot = 0) const override;
	private:
		uint32_t m_Width, m_Height;
		uint32_t m_ID;
	};
}
