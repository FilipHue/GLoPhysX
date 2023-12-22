#pragma once

#include "glophysx/rendering/camera/simple_camera.h"

namespace GLOPHYSX {

	using namespace RENDERING;

	namespace COMPONENTS {

		class SceneCamera : public SimpleCamera
		{
		public:
			enum class ProjectionType
			{
				PERSPECTIVE,
				ORTHOGRAPHIC
			};

		public:
			SceneCamera();
			virtual ~SceneCamera();

			void SetPerspectiveProjection(float fov, float near_z, float far_z);
			void SetOrthographicProjection(float size, float near_z, float far_z);

			void SetViewportSize(uint32_t width, uint32_t height);

			// PERSPECTIVE
			void SetPerspectiveProjectionFov(float fov) { m_perspective_fov = fov; RecalculateProjection(); }
			float GetPerspectiveProjectionFov() const { return m_perspective_fov; }

			float GetPerspectiveNearZ() const { return m_perspective_near; };
			void SetPerspectiveNearZ(float near_z) { m_perspective_near = near_z; RecalculateProjection(); };

			float GetPerspectiveFarZ() const { return m_perspective_far; };
			void SetPerspectiveFarZ(float far_z) { m_perspective_far = far_z; RecalculateProjection(); };

			// ORTHOGRAPHIC
			void SetOrthographicProjectionSize(float size) { m_ortho_size = size; RecalculateProjection(); }
			float GetOrthographicProjectionSize() const { return m_ortho_size;  }

			float GetOrthographicNearZ() const { return m_ortho_near; };
			void SetOrthographicNearZ(float near_z) { m_ortho_near = near_z; RecalculateProjection(); };

			float GetOrthographicFarZ() const { return m_ortho_far; };
			void SetOrthographicFarZ(float far_z) { m_ortho_far = far_z; RecalculateProjection(); };

			ProjectionType GetProjectionType() const { return m_projection_type; }
			void SetProjectionType(ProjectionType projection_type) { m_projection_type = projection_type; RecalculateProjection(); }

		private:
			void RecalculateProjection();

		private:
			ProjectionType m_projection_type = ProjectionType::ORTHOGRAPHIC;

			float m_perspective_fov = glm::radians(45.f);
			float m_perspective_near = 0.01f;
			float m_perspective_far = 1000.f;

			float m_ortho_size = 10.f;
			float m_ortho_near = -1.f;
			float m_ortho_far  = 1.f;

			float m_aspect_ratio = 0.0f;
		};
	}
}
