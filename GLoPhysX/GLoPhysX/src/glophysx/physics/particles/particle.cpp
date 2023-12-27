#include "gxpch.h"
#include "particle.h"

namespace GLOPHYSX {

	namespace PHYSICS {

		void Particle::Integrate(DeltaTime dt)
		{
			m_position += m_velocity * (float)dt;
			m_velocity += m_acceleration * (float)dt;
			m_velocity *= glm::pow(m_damepening, (float)dt);
		}
	}
}
