#include "gxpch.h"
#include "opengl_texture_2D.h"

#include "glad/glad.h"
#include "stb_image.h"

namespace GLOPHYSX {

	namespace RENDERING {

		static constexpr GLuint pixel_format[5] = { 0, GL_RED, GL_RG, GL_RGB, GL_RGBA };
		static constexpr GLuint internal_format[4][5] = {
			{ 0, GL_R8, GL_RG8, GL_RGB8, GL_RGBA8 },
			{ 0, GL_R16, GL_RG16, GL_RGB16, GL_RGBA16 },
			{ 0, GL_R16F, GL_RG16F, GL_RGB16F, GL_RGBA16F },
			{ 0, GL_R32F, GL_RG32F, GL_RGB32F, GL_RGBA32F }
		};

		OpenglTexture2D::OpenglTexture2D(const std::string& path, uint32_t x_offset, uint32_t y_offset)
		{
			m_path = path;

			stbi_set_flip_vertically_on_load(1);

			int width, height, channels;
			stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
			if (data == nullptr) {
				GLOP_CORE_WARN("Unable to load texture: {0}", path);
				exit(-1);
			}

			m_width = width;
			m_height = height;

			glCreateTextures(GL_TEXTURE_2D, 1, &m_id);
			glTextureStorage2D(m_id, 1, internal_format[0][channels], m_width, m_height);

			glTextureParameteri(m_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTextureParameteri(m_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			glTextureSubImage2D(m_id, 0, x_offset, y_offset, m_width, m_height, pixel_format[channels], GL_UNSIGNED_BYTE, data);

			stbi_image_free(data);
		}
		OpenglTexture2D::~OpenglTexture2D()
		{
			glDeleteTextures(1, &m_id);
		}
		void OpenglTexture2D::Bind(uint32_t slot) const
		{
			glBindTextureUnit(slot, m_id);
		}
	}
}
