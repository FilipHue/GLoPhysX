#pragma once

#include "glophysx/components/scene/scene_camera.h"

namespace GLOPHYSX {

	namespace COMPONENTS {

		struct CameraComponent
		{
			SceneCamera m_camera;

			bool is_primary = true;
			bool fixed_aspect_ratio = false;

			CameraComponent() = default;
			CameraComponent(const CameraComponent&) = default;
		};
	}
}
