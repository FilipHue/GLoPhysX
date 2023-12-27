#pragma once

#include "opengl_shader_utils.h"

namespace GLOPHYSX {

	namespace RENDERING {

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
			void CompileOrGetVulkanBinaries(const std::unordered_map<ShaderType, std::string>& shader_sources);
			void CompileOrGetOpenglBinaries();

			void CreateProgram();

			void Reflect(GLenum stage, const std::vector<uint32_t>& shader_data);

		private:
			uint32_t m_id;

			std::filesystem::path m_file_path;
			std::string m_name;

			std::unordered_map<GLenum, std::vector<uint32_t>> m_vulkan_SPIRV;
			std::unordered_map<GLenum, std::vector<uint32_t>> m_opengl_SPIRV;

			std::unordered_map<GLenum, std::string> m_opengl_source_code;
		};
	}
}
