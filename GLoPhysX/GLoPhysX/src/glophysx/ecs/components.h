#pragma once

#include "glophysx/core/core.h"
#include "glophysx/components/scene/scene_camera.h"

#define GLM_ENABLE_EXPERIMENTAL
#include "gtx/quaternion.hpp"

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

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
			glm::vec3 m_translation = { 0.0f, 0.0f, 0.0f };
			glm::vec3 m_rotation = { 0.0f, 0.0f, 0.0f };
			glm::vec3 m_scale = { 1.0f, 1.0f, 1.0f };

			TransformComponent() = default;
			TransformComponent(const TransformComponent&) = default;
			TransformComponent(const glm::vec3& translation) : m_translation(translation) {}

			glm::mat4 GetTransform() const
			{
				return 
					glm::translate(glm::mat4(1.f), m_translation) *
					glm::toMat4(glm::quat(m_rotation)) *
					glm::scale(glm::mat4(1.0f), m_scale);
			}
		};

		struct SpriteComponent
		{
			glm::vec4 m_color = glm::vec4(1.0f);

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
