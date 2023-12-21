#pragma once

#include "glophysx/core/core.h"
#include "glophysx/components/scene/scene_camera.h"

#include "glm.hpp"

namespace GLOPHYSX {

	namespace COMPONENTS {

		struct TagComponent
		{
			std::string m_tag;

			TagComponent() = default;
			TagComponent(const TagComponent&) = default;
			TagComponent(const std::string& tag) : m_tag(tag) {}
		};

		struct TransformComponent
		{
			glm::mat4 m_transform = glm::mat4(1.f);

			TransformComponent() = default;
			TransformComponent(const TransformComponent&) = default;
			TransformComponent(const glm::mat4& transform) : m_transform(transform) {}

			operator glm::mat4& () { return m_transform; }
			operator const glm::mat4& () { return m_transform; }
		};

		struct SpriteComponent
		{
			glm::vec4 m_color = glm::vec4(1.f);

			SpriteComponent() = default;
			SpriteComponent(const SpriteComponent&) = default;
			SpriteComponent(const glm::vec4& color) : m_color(color) {}
		};

		struct CameraComponent
		{
			SceneCamera m_camera;

			bool is_primary = true;
			bool fixed_aspect_ratio = false;

			CameraComponent() = default;
			CameraComponent(const CameraComponent&) = default;
		};
	}
}
