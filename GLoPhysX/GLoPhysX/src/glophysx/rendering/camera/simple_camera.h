#pragma once

#include "glophysx/core/core.h"
#include "glm.hpp"

namespace GLOPHYSX {

	namespace RENDERING {

		class SimpleCamera {
		public:
			SimpleCamera() = default;
			SimpleCamera(const glm::mat4& projection) : m_projection_matrix(projection) {}
			virtual ~SimpleCamera() = default;

			GLOP_API const glm::mat4& GetProjectionMatrix() const { return m_projection_matrix; }

		protected:
			glm::mat4 m_projection_matrix;
		};
	}
}
