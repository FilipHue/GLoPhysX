#pragma once

#include "glm.hpp"

namespace GLOPHYSX {

	namespace COMPONENTS {

		struct EdgeColliderComponent {

			glm::vec2 offset = { 0.0f, 0.0f };
			glm::vec2 start = { -0.5f, 0.0f };
			glm::vec2 stop = { 0.5f, 0.0f };

			void* runtime_fixtures = nullptr;

			EdgeColliderComponent() = default;
			EdgeColliderComponent(const EdgeColliderComponent&) = default;
		};
	}
}