#pragma once

#include "glophysx/core/core.h"

#include "simple_camera.h"

namespace GLOPHYSX {

	namespace RENDERING {

		class Camera : public SimpleCamera {
		public:
			Camera() = default;
			virtual ~Camera() = default;

			GLOP_API const glm::mat4& GetViewMatrix() const { return m_view_matrix; }
			GLOP_API const glm::mat4& GetVPMatrix() const { return m_view_projection_matrix; }

		protected:
			glm::mat4 m_view_matrix;
			glm::mat4 m_view_projection_matrix;
		};
	}
}
