#pragma once

#include "glm.hpp"

namespace GLOPHYSX {

	namespace COMPONENTS {

		struct BoxCollider2DComponent {

			glm::vec2 offset = { 0.0f, 0.0f };
			glm::vec2 size = { 0.5f, 0.5f };

			float density = 1.0f;
			float friction = 0.5f;
			float restitution = 0.0f;
			float restitution_treshold = 0.05f;

			void* runtime_fixtures = nullptr;

			BoxCollider2DComponent() = default;
			BoxCollider2DComponent(const BoxCollider2DComponent&) = default;
		};
	}
}