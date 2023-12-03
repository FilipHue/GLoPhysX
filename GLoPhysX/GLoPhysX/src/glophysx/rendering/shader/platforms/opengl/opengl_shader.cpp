#include "gxpch.h"
#include "opengl_shader.h"

#include "glad/glad.h"

#include "gtc/type_ptr.hpp"

namespace GLOPHYSX {

	namespace RENDERER {
		OpenglShader::OpenglShader(std::string& source_vs, std::string& source_fs)
		{
			// Vertex shader
			GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);

			const GLchar* source = (const GLchar*)source_vs.c_str();
			glShaderSource(vertex_shader, 1, &source, 0);

			glCompileShader(vertex_shader);

			GLint compiled = 0;
			glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &compiled);
			if (compiled == GL_FALSE) {
				GLint log_length = 0;
				glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &log_length);

				std::vector<GLchar> info_log(log_length);
				glGetShaderInfoLog(vertex_shader, log_length, &log_length, &info_log[0]);

				glDeleteShader(vertex_shader);

				GLOP_CORE_WARN("VERTEX SHADER COMPILATION FAILED\n{0}", info_log.data());

				return;
			}

			// Fragment shader
			GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

			source = (const GLchar*)source_fs.c_str();
			glShaderSource(fragment_shader, 1, &source, 0);

			glCompileShader(fragment_shader);

			compiled = 0;
			glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &compiled);
			if (compiled == GL_FALSE) {
				GLint log_length = 0;
				glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &log_length);

				std::vector<GLchar> info_log(log_length);
				glGetShaderInfoLog(fragment_shader, log_length, &log_length, &info_log[0]);

				glDeleteShader(fragment_shader);

				GLOP_CORE_WARN("FRAGMENT SHADER COMPILATION FAILED\n{0}", info_log.data());

				return;
			}

			// Linking
			m_id = glCreateProgram();

			glAttachShader(m_id, vertex_shader);
			glAttachShader(m_id, fragment_shader);

			glLinkProgram(m_id);

			GLint linked = 0;
			glGetProgramiv(m_id, GL_LINK_STATUS, (int*) & linked);
			if (linked == GL_FALSE) {
				GLint log_length = 0;
				glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &log_length);

				std::vector<GLchar> info_log(log_length);
				glGetProgramInfoLog(m_id, log_length, &log_length, &info_log[0]);

				glDeleteProgram(m_id);

				glDeleteShader(vertex_shader);
				glDeleteShader(fragment_shader);

				GLOP_CORE_WARN("SHADER PROGRAM LINKING FAILED\n{0}", info_log.data());

				return;
			}

			glDetachShader(m_id, vertex_shader);
			glDetachShader(m_id, fragment_shader);

			m_types = VERTEX | FRAGMENT;
		}
		OpenglShader::~OpenglShader()
		{
			glDeleteProgram(m_id);
		}

		void OpenglShader::Bind() const
		{
			glUseProgram(m_id);
		}
		void OpenglShader::Unbind() const
		{
			glUseProgram(0);
		}

		void OpenglShader::SetBool(const std::string& name, bool value) const
		{
			SendUniformBool(name, value);
		}
		void OpenglShader::SetInt(const std::string& name, int value) const
		{
			SendUniformInt(name, value);
		}
		void OpenglShader::SetIVec2(const std::string& name, const glm::ivec2& value) const
		{
			SendUniformIVec2(name, value);
		}
		void OpenglShader::SetIVec3(const std::string& name, const glm::ivec3& value) const
		{
			SendUniformIVec3(name, value);
		}
		void OpenglShader::SetIVec4(const std::string& name, const glm::ivec4& value) const
		{
			SendUniformIVec4(name, value);
		}
		void OpenglShader::SetFloat(const std::string& name, float value) const
		{
			SendUniformFloat(name, value);
		}
		void OpenglShader::SetVec2(const std::string& name, const glm::vec2& value) const
		{
			SendUniformVec2(name, value);
		}
		void OpenglShader::SetVec3(const std::string& name, const glm::vec3& value) const
		{
			SendUniformVec3(name, value);
		}
		void OpenglShader::SetVec4(const std::string& name, const glm::vec4& value) const
		{
			SendUniformVec4(name, value);
		}
		void OpenglShader::SetMat2(const std::string& name, const glm::mat2& value) const
		{
			SendUniformMat2(name, value);
		}
		void OpenglShader::SetMat3(const std::string& name, const glm::mat3& value) const
		{
			SendUniformMat3(name, value);
		}
		void OpenglShader::SetMat4(const std::string& name, const glm::mat4& value) const
		{
			SendUniformMat4(name, value);
		}

		void OpenglShader::SendUniformBool(const std::string& name, bool value) const
		{
			GLint location = glGetUniformLocation(m_id, name.c_str());
			glUniform1i(location, (int)value);
		}
		void OpenglShader::SendUniformInt(const std::string& name, int value) const
		{
			GLint location = glGetUniformLocation(m_id, name.c_str());
			glUniform1i(location, value);
		}
		void OpenglShader::SendUniformIVec2(const std::string& name, const glm::ivec2& value) const
		{
			GLint location = glGetUniformLocation(m_id, name.c_str());
			glUniform2i(location, value.x, value.y);
		}
		void OpenglShader::SendUniformIVec3(const std::string& name, const glm::ivec3& value) const
		{
			GLint location = glGetUniformLocation(m_id, name.c_str());
			glUniform3i(location, value.x, value.y, value.z);
		}
		void OpenglShader::SendUniformIVec4(const std::string& name, const glm::ivec4& value) const
		{
			GLint location = glGetUniformLocation(m_id, name.c_str());
			glUniform4i(location, value.x, value.y, value.z, value.w);
		}
		void OpenglShader::SendUniformFloat(const std::string& name, float value) const
		{
			GLint location = glGetUniformLocation(m_id, name.c_str());
			glUniform1f(location, value);
		}
		void OpenglShader::SendUniformVec2(const std::string& name, const glm::vec2& value) const
		{
			GLint location = glGetUniformLocation(m_id, name.c_str());
			glUniform2f(location, value.x, value.y);
		}
		void OpenglShader::SendUniformVec3(const std::string& name, const glm::vec3& value) const
		{
			GLint location = glGetUniformLocation(m_id, name.c_str());
			glUniform3f(location, value.x, value.y, value.z);
		}
		void OpenglShader::SendUniformVec4(const std::string& name, const glm::vec4& value) const
		{
			GLint location = glGetUniformLocation(m_id, name.c_str());
			glUniform4f(location, value.x, value.y, value.z, value.w);
		}
		void OpenglShader::SendUniformMat2(const std::string& name, const glm::mat2& value) const
		{
			GLint location = glGetUniformLocation(m_id, name.c_str());
			glUniformMatrix2fv(location, 1, GL_FALSE, glm::value_ptr(value));
		}
		void OpenglShader::SendUniformMat3(const std::string& name, const glm::mat3& value) const
		{
			GLint location = glGetUniformLocation(m_id, name.c_str());
			glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(value));
		}
		void OpenglShader::SendUniformMat4(const std::string& name, const glm::mat4& value) const
		{
			GLint location = glGetUniformLocation(m_id, name.c_str());
			glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
		}
	}
}
