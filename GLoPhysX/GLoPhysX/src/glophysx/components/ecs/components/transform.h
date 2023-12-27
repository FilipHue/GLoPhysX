#pragma once

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include "gtx/quaternion.hpp"

namespace GLOPHYSX {

	namespace COMPONENTS {

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
	}
}
