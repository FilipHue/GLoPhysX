#pragma once

#include "glophysx/core/core.h"

namespace GLOPHYSX {

	class DeltaTime
	{
	public:
		GLOP_API DeltaTime(float delta_time = 0.0f) { m_delta_time = delta_time; }

		GLOP_API float GetDeltaTimeSec() const { return m_delta_time; }
		GLOP_API float GetDeltaTimeMil() const { return m_delta_time * 1000.f; }

		GLOP_API operator float() const { return m_delta_time; }

	private:
		float m_delta_time = 0.0f;
	};
}
