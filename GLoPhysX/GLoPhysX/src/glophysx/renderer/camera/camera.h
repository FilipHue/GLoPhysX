#pragma once

#include "glophysx/core/core.h"
#include "glm.hpp"

namespace GLOPHYSX {

	namespace RENDERER {

		class Camera {
		public:
			virtual ~Camera() = default;

			GLOP_API const glm::mat4& GetProjectionMatrix() const { return m_projection_matrix; }
			GLOP_API const glm::mat4& GetViewMatrix() const { return m_view_matrix; }
			GLOP_API const glm::mat4& GetVPMatrix() const { return m_view_projection_matrix; }

		protected:
			glm::mat4 m_projection_matrix;
			glm::mat4 m_view_matrix;
			glm::mat4 m_view_projection_matrix;
		};
	}
}
