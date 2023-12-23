#include "gxpch.h"
#include "scene_camera.h"

#include "gtc/matrix_transform.hpp"

namespace GLOPHYSX {

	namespace COMPONENTS {

		SceneCamera::SceneCamera()
		{
			RecalculateProjection();
		}

		SceneCamera::~SceneCamera()
		{
		}

		void SceneCamera::SetPerspectiveProjection(float fov, float near_z, float far_z)
		{
			m_perspective_fov = fov;
			m_perspective_near = near_z;
			m_perspective_far = far_z;

			m_projection_type = ProjectionType::PERSPECTIVE;

			RecalculateProjection();
		}

		void SceneCamera::SetOrthographicProjection(float size, float near_z, float far_z)
		{
			m_ortho_size = size;
			m_ortho_near = near_z;
			m_ortho_far = far_z;

			m_projection_type = ProjectionType::ORTHOGRAPHIC;

			RecalculateProjection();
		}
		void SceneCamera::SetViewportSize(uint32_t width, uint32_t height)
		{
			m_aspect_ratio = (float)width / (float)height;

			RecalculateProjection();
		}

		void SceneCamera::RecalculateProjection()
		{
			if (m_projection_type == ProjectionType::PERSPECTIVE)
			{
				m_projection_matrix = glm::perspective(m_perspective_fov, m_aspect_ratio, m_perspective_near, m_perspective_far);
			}

			if (m_projection_type == ProjectionType::ORTHOGRAPHIC) {
				float ortho_left = -m_ortho_size * m_aspect_ratio * 0.5f;
				float ortho_right = m_ortho_size * m_aspect_ratio * 0.5f;
				float ortho_bottom = -m_ortho_size * 0.5f;
				float ortho_up = m_ortho_size * 0.5f;

				m_projection_matrix = glm::ortho(ortho_left, ortho_right, ortho_bottom, ortho_up, m_ortho_near, m_ortho_far);
			}
		}
	}
}
