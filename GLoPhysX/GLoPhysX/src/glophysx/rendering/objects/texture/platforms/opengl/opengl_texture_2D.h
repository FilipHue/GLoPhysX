#pragma once

#include "glophysx/rendering/objects/texture/texture.h"

namespace GLOPHYSX {

	namespace RENDERING {

		class OpenglTexture2D : public Texture2D
		{
		public:
			OpenglTexture2D(const std::string& path, int flip = 0, uint32_t x_offset = 0, uint32_t y_offset = 0);
			OpenglTexture2D(uint32_t width, uint32_t height);
			virtual ~OpenglTexture2D();

			virtual uint32_t GetWidth() const override { return m_width; }
			virtual uint32_t GetHeight() const override { return m_height; }

			virtual void SetData(void* data, uint32_t size) override;

			virtual void Bind(uint32_t slot = 0) const override;

		private:
			std::string m_path;

			uint32_t m_width;
			uint32_t m_height;

			uint32_t m_id;
		};
	}
}
