#pragma once

#include "glm.hpp"

namespace GLOPHYSX {

	namespace COMPONENTS {

		struct CircleRendererComponent
		{
			glm::vec4 m_color = glm::vec4(1.0f);
			float m_thickness = 1.0f;
			float m_fade = 0.005f;

			CircleRendererComponent() = default;
			CircleRendererComponent(const CircleRendererComponent&) = default;
		};
	}
}