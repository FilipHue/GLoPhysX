#pragma once

#include "glophysx/rendering/objects/texture/texture.h"

#include <filesystem>

namespace GLOPHYSX {

	namespace EDITOR {

		using namespace RENDERING;

		class ContentBrowser
		{
		public:
			ContentBrowser();

			void Render();

		private:
			const float m_padding = 16.0f;
			const float m_thumbnail_size = 64.0f;
			const float m_cell_size = m_padding + m_thumbnail_size;

			std::filesystem::path m_current_directory;
			Shared<Texture2D> m_directory_icon;
			Shared<Texture2D> m_file_icon;
			Shared<Texture2D> m_back_icon;
		};
	}
}
