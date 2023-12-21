#pragma once

#include "glophysx/core/core.h"
#include "glophysx/components/scene/scene_camera.h"

#include "glm.hpp"

namespace GLOPHYSX {

	namespace COMPONENTS {

		class ScriptableEntity;

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

		struct NativeScriptComponent
		{
			ScriptableEntity* m_instance = nullptr;

			ScriptableEntity* (*InstantiateScript)();
			void(*DestroyScript)(NativeScriptComponent*);
			std::function<void()> DestroyFn;

			template<typename T>
			void Bind()
			{
				InstantiateScript = []() { return static_cast<ScriptableEntity*>(new T()); };
				DestroyScript = [](NativeScriptComponent* nsc) { delete nsc->m_instance; nsc->m_instance = nullptr; };
			}

			NativeScriptComponent() = default;
			NativeScriptComponent(const NativeScriptComponent&) = default;
		};
	}
}
