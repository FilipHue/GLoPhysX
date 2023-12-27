#pragma once

#include "glophysx/physics/glm_utils.h"

namespace GLOPHYSX {

	namespace PHYSICS {

		class Rigidbody2D
		{
		public:
			Rigidbody2D() = default;
			Rigidbody2D(glm::vec3& position, glm::vec3& velocity, glm::vec3& acceleration, float dampening)
				: m_position(position), m_velocity(velocity), m_acceleration(acceleration), m_linear_damepening(dampening) {}

			glm::vec3 GetPosition() { return m_position; };
			glm::vec3 GetVelocity() { return m_velocity; };
			glm::vec3 GetAcceleration() { return m_acceleration; };
			float GetDampening() const { return m_linear_damepening; }

			const glm::vec3& GetPosition() const { return m_position; };
			const glm::vec3& GetVelocity() const { return m_velocity; };
			const glm::vec3& GetAcceleration() const { return m_acceleration; };

			void Integrate(DeltaTime dt);

		protected:
			glm::vec3 m_position = glm::vec3(0.0f);
			glm::vec3 m_velocity = glm::vec3(0.0f);
			glm::vec3 m_acceleration = glm::vec3(0.0f);

			glm::vec3 rotation;
			glm::quat orientation;

			glm::mat4 transform;

			float m_inverse_mass = 1.0f;
			float m_linear_damepening = 0.999f;

		};
	}
}
