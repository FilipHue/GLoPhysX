#pragma once

#include "glophysx/core/core.h"

#include "glm.hpp"

namespace GLOPHYSX {

	namespace RENDERER {

		enum ShaderType {
			NONE,
			VERTEX = 1,
			GEOMETRY = 2,
			TESSELATION = 4,
			COMPUTE = 8,
			FRAGMENT = 16,
			PIXEL = 32,
			HULL = 64 // Direct3D nomenclature
		};

		class Shader
		{
		public:
			Shader() = default;
			GLOP_API ~Shader() = default;

			GLOP_API virtual void Bind() const = 0;
			GLOP_API virtual void Unbind() const = 0;

			GLOP_API virtual void SetBool(const std::string& name, bool value) const = 0;

			GLOP_API virtual void SetInt(const std::string& name, int value) const = 0;
			GLOP_API virtual void SetIVec2(const std::string& name, const glm::ivec2& value) const = 0;
			GLOP_API virtual void SetIVec3(const std::string& name, const glm::ivec3& value) const = 0;
			GLOP_API virtual void SetIVec4(const std::string& name, const glm::ivec4& value) const = 0;

			GLOP_API virtual void SetFloat(const std::string& name, float value) const = 0;
			GLOP_API virtual void SetVec2(const std::string& name, const glm::vec2& value) const = 0;
			GLOP_API virtual void SetVec3(const std::string& name, const glm::vec3& value) const = 0;
			GLOP_API virtual void SetVec4(const std::string& name, const glm::vec4& value) const = 0;

			GLOP_API virtual void SetMat2(const std::string& name, const glm::mat2& value) const = 0;
			GLOP_API virtual void SetMat3(const std::string& name, const glm::mat3& value) const = 0;
			GLOP_API virtual void SetMat4(const std::string& name, const glm::mat4& value) const = 0;

			GLOP_API const int GetType() const { return m_types; }
			GLOP_API const int HasType(ShaderType type) const { return m_types & type; }

			GLOP_API static std::shared_ptr<Shader> Create(std::string& source_vs, std::string& source_fs);

		protected:
			int m_types = NONE;
		};
	}
}
