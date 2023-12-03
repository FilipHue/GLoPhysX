#pragma once

#include "glophysx/core/core.h"
#include "glophysx/rendering/camera/camera.h"
#include "glm.hpp"

namespace GLOPHYSX {

	namespace RENDERING {

		class OrthographicCamera : public Camera
		{
		public:
			GLOP_API OrthographicCamera(float left, float right, float bottom, float top, float z_near=-1.f, float z_far=1.f);

			GLOP_API void SetPosition(const glm::vec3& position) { m_position = position; RecalculateVPMatrix(); }
			GLOP_API void SetRotation(const float& rotation) { m_rotation = rotation; RecalculateVPMatrix(); }

			GLOP_API const glm::vec3& GetPosition() const { return m_position; }
			GLOP_API const float& GetRotation() const { return m_rotation; }

		private:
			void RecalculateVPMatrix();

			glm::vec3 m_position = glm::vec3(0.f);
			float m_rotation = 0.0f;

			float m_z_near;
			float m_z_far;
		};
	}
}

