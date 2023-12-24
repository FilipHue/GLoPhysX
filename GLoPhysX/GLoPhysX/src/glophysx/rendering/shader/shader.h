#pragma once

#include "shader_utils.h"

#include "glm.hpp"

namespace GLOPHYSX {

	namespace RENDERING {

		class Shader
		{
		public:
			Shader() = default;
			GLOP_API ~Shader() = default;

			GLOP_API virtual void Bind() const = 0;
			GLOP_API virtual void Unbind() const = 0;

			GLOP_API virtual void SetBool(const std::string&  name, bool value) const = 0;

			GLOP_API virtual void SetInt(const std::string&   name, int value) const = 0;
			GLOP_API virtual void SetIVec2(const std::string& name, const glm::ivec2& value) const = 0;
			GLOP_API virtual void SetIVec3(const std::string& name, const glm::ivec3& value) const = 0;
			GLOP_API virtual void SetIVec4(const std::string& name, const glm::ivec4& value) const = 0;

			GLOP_API virtual void SetIntValues(const std::string& name, int* values, uint32_t count) const = 0;

			GLOP_API virtual void SetFloat(const std::string& name, float value) const = 0;
			GLOP_API virtual void SetVec2(const std::string&  name, const glm::vec2& value) const = 0;
			GLOP_API virtual void SetVec3(const std::string&  name, const glm::vec3& value) const = 0;
			GLOP_API virtual void SetVec4(const std::string&  name, const glm::vec4& value) const = 0;

			GLOP_API virtual void SetMat2(const std::string&  name, const glm::mat2& value) const = 0;
			GLOP_API virtual void SetMat3(const std::string&  name, const glm::mat3& value) const = 0;
			GLOP_API virtual void SetMat4(const std::string&  name, const glm::mat4& value) const = 0;

			GLOP_API const int GetType() const { return m_types; }
			GLOP_API const int HasType(ShaderType type) const { return m_types & type; }

			GLOP_API static Shared<Shader> Create(const std::string& file_path);
			GLOP_API static Shared<Shader> Create(const std::string& name, std::string& source_vs, std::string& source_fs);
			GLOP_API std::string GetName() { return m_name; }

		protected:
			static std::string ReadShaderSource(const std::string& file_path);
			static std::unordered_map<ShaderType, std::string> ProcessShaderSource(const std::string& source);

		protected:
			int m_types = NONE;
			std::string m_name;
		};
	}
}
