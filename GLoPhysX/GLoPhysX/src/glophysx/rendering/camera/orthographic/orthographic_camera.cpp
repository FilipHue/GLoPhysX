#include "gxpch.h"
#include "orthographic_camera.h"

#ifdef GLOP_DEBUG
	#include "glophysx/debug/debug.h"
#endif

#include "gtc/matrix_transform.hpp"

namespace GLOPHYSX {

	namespace RENDERING {

		OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float z_near, float z_far)
		{
			GLOP_PROFILE_FUNCTION();

			m_z_near = z_near;
			m_z_far = z_far;

			m_projection_matrix = glm::ortho(left, right, bottom, top, m_z_near, m_z_far);

			m_view_matrix = glm::mat4(1.f);
			m_view_projection_matrix = m_view_matrix * m_projection_matrix;
		}

		GLOP_API void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
		{
			GLOP_PROFILE_FUNCTION();

			m_projection_matrix = glm::ortho(left, right, bottom, top, m_z_near, m_z_far);
			m_view_projection_matrix = m_view_matrix * m_projection_matrix;
		}

		void OrthographicCamera::RecalculateVPMatrix()
		{
			GLOP_PROFILE_FUNCTION();

			glm::mat4 transform = glm::translate(glm::mat4(1.f), m_position) * glm::rotate(glm::mat4(1.f), glm::radians(m_rotation), glm::vec3(0, 0, 1));

			m_view_matrix = glm::inverse(transform);
			m_view_projection_matrix = m_projection_matrix * m_view_matrix;
		}
	}
}
