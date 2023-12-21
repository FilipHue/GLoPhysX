#pragma once

#include "glophysx/rendering/camera/simple_camera.h"

namespace GLOPHYSX {

	using namespace RENDERING;

	namespace COMPONENTS {

		class SceneCamera : public SimpleCamera
		{
		public:
			SceneCamera();
			virtual ~SceneCamera();

			void SetOrthographicProjection(float size, float near_z, float far_z);

			void SetOrthographicProjectionSize(float size) { m_ortho_size = size; RecalculateProjection(); }
			float GetOrthographicProjectionSize() const { return m_ortho_size;  }

			void SetViewportSize(uint32_t width, uint32_t height);

		private:
			void RecalculateProjection();

		private:
			float m_ortho_size = 10.f;
			float m_ortho_near = -1.f;
			float m_ortho_far  = 1.f;

			float m_aspect_ratio = 0.0f;
		};
	}
}
