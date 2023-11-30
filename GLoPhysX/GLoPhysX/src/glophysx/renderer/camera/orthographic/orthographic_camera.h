#pragma once

#include "glophysx/core/core.h"
#include "glm.hpp"

namespace GLOPHYSX {

	namespace RENDERER {

		class OrthographicCamera
		{
		public:
			GLOP_API OrthographicCamera(float left, float right, float bottom, float top, float z_near=-1.f, float z_far=1.f);

			GLOP_API void SetPosition(const glm::vec3& position) { m_position = position; RecalculateViewMatrix(); }
			GLOP_API void SetRotation(const float& rotation) { m_rotation = rotation; RecalculateViewMatrix(); }

			GLOP_API const glm::vec3& GetPosition() const { return m_position; }
			GLOP_API const float& GetRotation() const { return m_rotation; }

			GLOP_API const glm::mat4& GetProjectionMatrix() const { return m_projection_matrix; }
			GLOP_API const glm::mat4& GetViewMatrix() const { return m_view_matrix; }
			GLOP_API const glm::mat4& GetVPMatrix() const { return m_view_projection_matrix; }

		private:
			void RecalculateViewMatrix();

		private:
			glm::mat4 m_projection_matrix;
			glm::mat4 m_view_matrix;
			glm::mat4 m_view_projection_matrix;

			glm::vec3 m_position = glm::vec3(0.f);
			float m_rotation = 0.0f;

			float m_z_near;
			float m_z_far;
		};
	}
}

