#include "lfpch.h"

#include "Platform/OpenGL/OpenGLTexture.h"

#include <stb/stb_image.h>
#include <glad/glad.h>

namespace Leaf {

	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
	{
		//Load Texture
		stbi_set_flip_vertically_on_load(true);
		int width, height, channels;

		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);

		LF_CORE_ASSERT(data, "Could not load image {0} ", path);

		m_Width = width; m_Height = height;

		GLenum internalFormat = 0, format = 0;

		if (channels == 4) {
			internalFormat = GL_RGBA8;
			format = GL_RGBA;
		}
		else if (channels == 3) {
			internalFormat = GL_RGB8;
			format = GL_RGB;
		}

		glCreateTextures(GL_TEXTURE_2D, 1, &m_ID);
		glTextureStorage2D(m_ID, 1, internalFormat, m_Width, m_Height);

		glTextureParameteri(m_ID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_ID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glPixelStoref(GL_UNPACK_ALIGNMENT, 1);

		glTextureSubImage2D(m_ID, 0, 0, 0, m_Width, m_Height, format, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}
	
	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_ID);
	}
	
	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, m_ID);
	}

}