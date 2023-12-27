#include "gxpch.h"
#include "mass_point.h"

namespace GLOPHYSX {

	namespace PHYSICS {
		void MassPoint::Integrate(DeltaTime dt)
		{
			if (m_inverse_mass <= 0.0f)
			{
				return;
			}

			m_position += m_velocity * (float)dt;
			m_velocity += m_acceleration * (float)dt;
			m_velocity *= glm::pow(m_damepening, dt);
		}
	}
}
