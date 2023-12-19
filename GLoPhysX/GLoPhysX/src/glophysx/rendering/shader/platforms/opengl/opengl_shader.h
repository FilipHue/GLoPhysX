#pragma once

#include "glophysx/rendering/shader/shader.h"
#include "glm.hpp"
#include "glad/glad.h"

namespace GLOPHYSX {

	namespace RENDERING {

		static GLenum GetShaderType(ShaderType type) {
			switch (type)
			{
			case GLOPHYSX::RENDERING::NONE:
				GLOP_CORE_WARN("Please spicify a shader type");
				exit(-1);
			case GLOPHYSX::RENDERING::VERTEX:
				return GL_VERTEX_SHADER;
			case GLOPHYSX::RENDERING::GEOMETRY:
				return GL_GEOMETRY_SHADER;
			case GLOPHYSX::RENDERING::TESSELATION:
				GLOP_CORE_WARN("Unsupported shader type by the current API");
				exit(-1);
			case GLOPHYSX::RENDERING::COMPUTE:
				GLOP_CORE_WARN("Unsupported shader type by the current API");
				exit(-1);
			case GLOPHYSX::RENDERING::FRAGMENT:
				return GL_FRAGMENT_SHADER;
			case GLOPHYSX::RENDERING::PIXEL:
				GLOP_CORE_WARN("Unsupported shader type by the current API");
				exit(-1);
			case GLOPHYSX::RENDERING::HULL:
				GLOP_CORE_WARN("Unsupported shader type by the current API");
				exit(-1);
			default:
				GLOP_CORE_WARN("Unkown shader type");
				exit(-1);
			}
		}

		class OpenglShader : public Shader
		{
		public:
			OpenglShader(const std::string& file_path);
			OpenglShader(const std::string& name, std::string& source_vs, std::string& source_fs);
			virtual ~OpenglShader();

			virtual void Bind() const override;
			virtual void Unbind() const override;

			virtual void SetBool(const std::string& name, bool value) const override;

			virtual void SetInt(const std::string& name, int value) const override;
			virtual void SetIVec2(const std::string& name, const glm::ivec2& value) const override;
			virtual void SetIVec3(const std::string& name, const glm::ivec3& value) const override;
			virtual void SetIVec4(const std::string& name, const glm::ivec4& value) const override;

			void SetIntValues(const std::string& name, int* values, uint32_t count) const override;

			virtual void SetFloat(const std::string& name, float value) const override;
			virtual void SetVec2(const std::string& name, const glm::vec2& value) const override;
			virtual void SetVec3(const std::string& name, const glm::vec3& value) const override;
			virtual void SetVec4(const std::string& name, const glm::vec4& value) const override;

			virtual void SetMat2(const std::string& name, const glm::mat2& value) const override;
			virtual void SetMat3(const std::string& name, const glm::mat3& value) const override;
			virtual void SetMat4(const std::string& name, const glm::mat4& value) const override;

			void SendUniformBool(const std::string& name, bool value) const;

			void SendUniformInt(const std::string& name, int value) const;
			void SendUniformIVec2(const std::string& name, const glm::ivec2& value) const;
			void SendUniformIVec3(const std::string& name, const glm::ivec3& value) const;
			void SendUniformIVec4(const std::string& name, const glm::ivec4& value) const;

			void SendUniformIntValues(const std::string& name, int* values, uint32_t count) const;

			void SendUniformFloat(const std::string& name, float value) const;
			void SendUniformVec2(const std::string& name, const glm::vec2& value) const;
			void SendUniformVec3(const std::string& name, const glm::vec3& value) const;
			void SendUniformVec4(const std::string& name, const glm::vec4& value) const;

			void SendUniformMat2(const std::string& name, const glm::mat2& value) const;
			void SendUniformMat3(const std::string& name, const glm::mat3& value) const;
			void SendUniformMat4(const std::string& name, const glm::mat4& value) const;

		private:
			void Compile(const std::unordered_map<ShaderType, std::string>& shader_sources);

		private:
			uint32_t m_id;
		};
	}
}
