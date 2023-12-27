#pragma once

#include "glophysx/rendering/objects/texture/texture.h"

#include "glm.hpp"

namespace GLOPHYSX {

	namespace COMPONENTS {

		struct SpriteComponent
		{
			glm::vec4 m_color = glm::vec4(1.0f);
			Shared<RENDERING::Texture2D> m_texture = nullptr;
			float m_tiling = 1.0f;

			SpriteComponent() = default;
			SpriteComponent(const SpriteComponent&) = default;
			SpriteComponent(const glm::vec4& color) : m_color(color) {}
		};
	}
}
