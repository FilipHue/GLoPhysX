#pragma once

#include "glophysx/rendering/shader/shader.h"
#include "glm.hpp"

namespace GLOPHYSX {

	namespace RENDERER {

		class OpenglShader : public Shader
		{
		public:
			OpenglShader(std::string& source_vs, std::string& source_fs);
			virtual ~OpenglShader();

			virtual void Bind() const override;
			virtual void Unbind() const override;

			virtual void SetBool(const std::string& name, bool value) const override;

			virtual void SetInt(const std::string& name, int value) const override;
			virtual void SetIVec2(const std::string& name, const glm::ivec2& value) const override;
			virtual void SetIVec3(const std::string& name, const glm::ivec3& value) const override;
			virtual void SetIVec4(const std::string& name, const glm::ivec4& value) const override;

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

			void SendUniformFloat(const std::string& name, float value) const;
			void SendUniformVec2(const std::string& name, const glm::vec2& value) const;
			void SendUniformVec3(const std::string& name, const glm::vec3& value) const;
			void SendUniformVec4(const std::string& name, const glm::vec4& value) const;

			void SendUniformMat2(const std::string& name, const glm::mat2& value) const;
			void SendUniformMat3(const std::string& name, const glm::mat3& value) const;
			void SendUniformMat4(const std::string& name, const glm::mat4& value) const;

		private:
			uint32_t m_id;
		};
	}
}
