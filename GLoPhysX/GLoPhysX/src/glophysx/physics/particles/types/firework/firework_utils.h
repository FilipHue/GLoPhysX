#pragma once

namespace GLOPHYSX {

	namespace PHYSICS {

		struct FireworkPayload
		{
			unsigned int m_type;
			unsigned int m_count;

			void SetPayload(unsigned int type, unsigned int count) { m_type = type, m_count = count; }
		};

		struct FireworkSpecification
		{
			// Type
			unsigned int m_type;

			// Time left before it detonates
			float m_delay;

			// Time left alive
			float m_min_age;
			float m_max_age;

			// Velocity
			float m_min_velocity;
			float m_max_velocity;

			// Dampening
			float m_dampening;

			unsigned int m_payload_count;
			FireworkPayload* m_payloads;

			FireworkSpecification() : m_payload_count(0), m_payloads(nullptr) {}
			~FireworkSpecification()
			{
				if (m_payloads)
				{
					delete[] m_payloads;
				}
			}
		};
	}
}
