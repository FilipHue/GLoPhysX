#pragma once

#include "glophysx/core/core.h"

#include <string>

namespace GLOPHYSX {

	namespace COMPONENTS {

		enum class BodyType {
			STATIC,
			KINEMATIC,
			DYNAMIC,
			NONE
		};

		static const std::string BodyTypeToString(BodyType type)
		{
			switch (type)
			{
			case GLOPHYSX::COMPONENTS::BodyType::STATIC:
				return "Static";
			case GLOPHYSX::COMPONENTS::BodyType::KINEMATIC:
				return "Kinematic";
			case GLOPHYSX::COMPONENTS::BodyType::DYNAMIC:
				return "Dynamic";
			}

			GLOP_CORE_WARN("Unknow rigidbody2d type.");

			return "None";
		}

		static BodyType StringToBodyType(const std::string type)
		{
			if (type == "Static")
			{
				return BodyType::STATIC;
			}
			if (type == "Kinematic")
			{
				return BodyType::KINEMATIC;
			}
			if (type == "Dynamic")
			{
				return BodyType::DYNAMIC;
			}

			GLOP_CORE_WARN("Unknown rigidbody2d type.");

			return BodyType::NONE;
		}

		struct RigidBody2DComponent {

			BodyType type = BodyType::STATIC;
			bool fixed_rotation = false;
			bool is_bullet = false;
			glm::vec2 linear_velocity = glm::vec2(0.f, 0.f);

			void* runtime_body = nullptr;

			RigidBody2DComponent() = default;
			RigidBody2DComponent(const RigidBody2DComponent&) = default;
		};
	}
}
