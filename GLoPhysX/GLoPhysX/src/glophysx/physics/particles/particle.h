#pragma once

#include "glophysx/core/core.h"
#include "glophysx/core/time/time.h"

#include "glophysx/rendering/objects/texture/texture.h"

#include "glm.hpp"

namespace GLOPHYSX {

	using namespace RENDERING;

	namespace PHYSICS {

		class Particle
		{
		public:
			Particle() = default;
			Particle(glm::vec3& position, glm::vec3& velocity, glm::vec3& acceleration, float dampening)
				: m_position(position), m_velocity(velocity), m_acceleration(acceleration), m_damepening(dampening) {}

			glm::vec3 GetPosition() { return m_position; };
			glm::vec3 GetVelocity() { return m_velocity; };
			glm::vec3 GetAcceleration() { return m_acceleration; };
			float GetDampening() const { return m_damepening; }

			const glm::vec3& GetPosition() const { return m_position; };
			const glm::vec3& GetVelocity() const { return m_velocity; };
			const glm::vec3& GetAcceleration() const { return m_acceleration; };

			virtual void Integrate(DeltaTime dt);

		protected:
			glm::vec3 m_position = glm::vec3(0.0f);
			glm::vec3 m_velocity = glm::vec3(0.0f);
			glm::vec3 m_acceleration = glm::vec3(0.0f);

			float m_damepening = 0.999f;
		};
	}
}
