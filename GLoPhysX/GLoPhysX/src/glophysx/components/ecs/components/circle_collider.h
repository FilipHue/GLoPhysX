#pragma once

#include "glm.hpp"

namespace GLOPHYSX {

	namespace COMPONENTS {

		struct CircleColliderComponent
		{
			glm::vec2 offset = { 0.0f, 0.0f };

			float radius = 0.5f;
			float density = 1.0f;
			float friction = 0.5f;
			float restitution = 0.0f;
			float restitution_treshold = 0.05f;

			void* runtime_fixtures = nullptr;

			CircleColliderComponent() = default;
			CircleColliderComponent(const CircleColliderComponent&) = default;
		};
	}
}
