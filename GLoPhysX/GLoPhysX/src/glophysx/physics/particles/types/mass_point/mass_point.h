#pragma once

#include "glophysx/physics/particles/particle.h"

namespace GLOPHYSX {

	namespace PHYSICS {

		class MassPoint : public Particle
		{
		public:
			MassPoint() : Particle() {};
			MassPoint(glm::vec3& position, glm::vec3& velocity, glm::vec3& acceleration, float dampening, float inverse_mass) :
				Particle(position, velocity, acceleration, dampening)
			{
				m_inverse_mass = inverse_mass;
			}

			void SetInverseMass(float inverse_mass) { m_inverse_mass = inverse_mass; }
			float GetInverseMass() const { return m_inverse_mass; }

			void Integrate(DeltaTime dt) override;

		private:
			float m_inverse_mass = 1.0f;
		};
	}
}
