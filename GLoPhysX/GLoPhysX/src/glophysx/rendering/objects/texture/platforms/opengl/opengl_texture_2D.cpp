#include "gxpch.h"
#include "opengl_texture_2D.h"

#include "glad/glad.h"
#include "stb_image.h"

#ifdef GLOP_DEBUG
	#include "glophysx/debug/debug.h"
#endif

namespace GLOPHYSX {

	namespace RENDERING {

		static constexpr GLuint pixel_format[5] = { 0, GL_RED, GL_RG, GL_RGB, GL_RGBA };
		static constexpr GLuint internal_format[4][5] = {
			{ 0, GL_R8, GL_RG8, GL_RGB8, GL_RGBA8 },
			{ 0, GL_R16, GL_RG16, GL_RGB16, GL_RGBA16 },
			{ 0, GL_R16F, GL_RG16F, GL_RGB16F, GL_RGBA16F },
			{ 0, GL_R32F, GL_RG32F, GL_RGB32F, GL_RGBA32F }
		};

		OpenglTexture2D::OpenglTexture2D(const std::string& path, int flip, uint32_t x_offset, uint32_t y_offset)
		{
			GLOP_PROFILE_FUNCTION();

			m_path = path;

			stbi_set_flip_vertically_on_load(flip);

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
			glTextureParameteri(m_id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glTextureParameteri(m_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTextureParameteri(m_id, GL_TEXTURE_WRAP_T, GL_REPEAT);

			glTextureSubImage2D(m_id, 0, x_offset, y_offset, m_width, m_height, pixel_format[channels], GL_UNSIGNED_BYTE, data);

			stbi_image_free(data);
		}

		OpenglTexture2D::OpenglTexture2D(uint32_t width, uint32_t height)
		{
			GLOP_PROFILE_FUNCTION();

			m_width = width;
			m_height = height;

			glCreateTextures(GL_TEXTURE_2D, 1, &m_id);
			glTextureStorage2D(m_id, 1, GL_RGBA8, m_width, m_height);

			glTextureParameteri(m_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTextureParameteri(m_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			glTextureParameteri(m_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTextureParameteri(m_id, GL_TEXTURE_WRAP_T, GL_REPEAT);
		}

		OpenglTexture2D::~OpenglTexture2D()
		{
			GLOP_PROFILE_FUNCTION();

			glDeleteTextures(1, &m_id);
		}

		void OpenglTexture2D::SetData(void* data, uint32_t size)
		{
			GLOP_PROFILE_FUNCTION();

			glTextureSubImage2D(m_id, 0, 0, 0, m_width, m_height, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}

		void OpenglTexture2D::Bind(uint32_t slot) const
		{
			GLOP_PROFILE_FUNCTION();

			glBindTextureUnit(slot, m_id);
		}
	}
}
