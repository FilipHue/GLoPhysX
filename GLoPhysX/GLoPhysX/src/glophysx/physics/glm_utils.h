#pragma once

#include "glophysx/core/time/time.h"

#include "glm.hpp"

namespace glm {

	glm::vec2 operator*(const glm::vec2& v, GLOPHYSX::DeltaTime dt)
	{
		return glm::vec2(v.x * dt, v.y * dt);
	}

	glm::vec3 operator*(const glm::vec3& v, GLOPHYSX::DeltaTime dt)
	{
		return glm::vec3(v.x * dt, v.y * dt, v.z * dt);
	}

	glm::vec4 operator*(const glm::vec4& v, GLOPHYSX::DeltaTime dt)
	{
		return glm::vec4(v.x * dt, v.y * dt, v.z * dt, v.w * dt);
	}
}
