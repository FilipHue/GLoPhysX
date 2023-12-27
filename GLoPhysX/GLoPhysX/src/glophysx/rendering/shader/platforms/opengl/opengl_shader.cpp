#include "gxpch.h"
#include "opengl_shader.h"

#ifdef GLOP_DEBUG
	#include "glophysx/debug/debug.h"
#endif

#include "glad/glad.h"
#include "gtc/type_ptr.hpp"

namespace GLOPHYSX {

	namespace RENDERING {

		OpenglShader::OpenglShader(const std::string& file_path)
		{
			GLOP_PROFILE_FUNCTION();

			auto last_separator = file_path.find_last_of("/\\");
			last_separator = last_separator == std::string::npos ? 0 : last_separator + 1;

			auto last_dot = file_path.rfind(".");
			auto name_size = last_dot == std::string::npos ? file_path.size() - last_separator : last_dot - last_separator;
			m_name = file_path.substr(last_separator, name_size);

			std::string source = ReadShaderSource(file_path);

			std::unordered_map<ShaderType, std::string> shader_sources = ProcessShaderSource(source);

			Compile(shader_sources);
		}

		OpenglShader::OpenglShader(const std::string& name, std::string& source_vs, std::string& source_fs)
		{
			GLOP_PROFILE_FUNCTION();

			m_name = name;

			std::unordered_map<ShaderType, std::string> shader_sources;

			shader_sources[VERTEX] = source_vs;
			shader_sources[FRAGMENT] = source_fs;

			Compile(shader_sources);
		}

		OpenglShader::~OpenglShader()
		{
			GLOP_PROFILE_FUNCTION();

			glDeleteProgram(m_id);
		}

		void OpenglShader::Bind() const
		{
			GLOP_PROFILE_FUNCTION();

			glUseProgram(m_id);
		}

		void OpenglShader::Unbind() const
		{
			GLOP_PROFILE_FUNCTION();

			glUseProgram(0);
		}

		// Shader API Commands
		void OpenglShader::SetBool(const std::string& name, bool value) const
		{
			GLOP_PROFILE_FUNCTION();

			SendUniformBool(name, value);
		}

		void OpenglShader::SetInt(const std::string& name, int value) const
		{
			GLOP_PROFILE_FUNCTION();

			SendUniformInt(name, value);
		}

		void OpenglShader::SetIVec2(const std::string& name, const glm::ivec2& value) const
		{
			GLOP_PROFILE_FUNCTION();

			SendUniformIVec2(name, value);
		}

		void OpenglShader::SetIVec3(const std::string& name, const glm::ivec3& value) const
		{
			GLOP_PROFILE_FUNCTION();

			SendUniformIVec3(name, value);
		}

		void OpenglShader::SetIVec4(const std::string& name, const glm::ivec4& value) const
		{
			GLOP_PROFILE_FUNCTION();

			SendUniformIVec4(name, value);
		}

		void OpenglShader::SetIntValues(const std::string& name, int* values, uint32_t count) const
		{
			GLOP_PROFILE_FUNCTION();

			SendUniformIntValues(name, values, count);
		}

		void OpenglShader::SetFloat(const std::string& name, float value) const
		{
			GLOP_PROFILE_FUNCTION();

			SendUniformFloat(name, value);
		}

		void OpenglShader::SetVec2(const std::string& name, const glm::vec2& value) const
		{
			GLOP_PROFILE_FUNCTION();

			SendUniformVec2(name, value);
		}

		void OpenglShader::SetVec3(const std::string& name, const glm::vec3& value) const
		{
			GLOP_PROFILE_FUNCTION();

			SendUniformVec3(name, value);
		}

		void OpenglShader::SetVec4(const std::string& name, const glm::vec4& value) const
		{
			GLOP_PROFILE_FUNCTION();

			SendUniformVec4(name, value);
		}

		void OpenglShader::SetMat2(const std::string& name, const glm::mat2& value) const
		{
			GLOP_PROFILE_FUNCTION();

			SendUniformMat2(name, value);
		}

		void OpenglShader::SetMat3(const std::string& name, const glm::mat3& value) const
		{
			GLOP_PROFILE_FUNCTION();

			SendUniformMat3(name, value);
		}

		void OpenglShader::SetMat4(const std::string& name, const glm::mat4& value) const
		{
			GLOP_PROFILE_FUNCTION();

			SendUniformMat4(name, value);
		}

		// OpenGL Shader Commands
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

		void OpenglShader::SendUniformIntValues(const std::string& name, int* values, uint32_t count) const
		{
			GLint location = glGetUniformLocation(m_id, name.c_str());
			glUniform1iv(location, count, values);
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

		// OpenGL Specific
		void OpenglShader::Compile(const std::unordered_map<ShaderType, std::string>& shader_sources)
		{
			GLuint program = glCreateProgram();
			std::vector<GLenum> shader_ids;
			shader_ids.reserve(shader_sources.size());

			for (std::pair<ShaderType, std::string> pair: shader_sources) {
				GLenum type = GetShaderType(pair.first);
				GLuint shader = glCreateShader(type);

				const GLchar* source = (const GLchar*)pair.second.c_str();
				glShaderSource(shader, 1, &source, 0);

				glCompileShader(shader);

				GLint compiled = 0;
				glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
				if (compiled == GL_FALSE) {
					GLint log_length = 0;
					glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);

					std::vector<GLchar> info_log(log_length);
					glGetShaderInfoLog(shader, log_length, &log_length, &info_log[0]);

					glDeleteShader(shader);

					GLOP_CORE_WARN("{0} SHADER COMPILATION FAILED\n{1}", ShaderTypeToString(pair.first), info_log.data());

					return;
				}

				shader_ids.push_back(shader);
				type |= ShaderTypeFromString(ShaderTypeToString(pair.first));

				glAttachShader(program, shader);
			}

			m_id = program;

			glLinkProgram(m_id);

			GLint linked = 0;
			glGetProgramiv(m_id, GL_LINK_STATUS, (int*)&linked);
			if (linked == GL_FALSE) {
				GLint log_length = 0;
				glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &log_length);

				std::vector<GLchar> info_log(log_length);
				glGetProgramInfoLog(m_id, log_length, &log_length, &info_log[0]);

				glDeleteProgram(m_id);

				for (GLenum id : shader_ids) {
					glDeleteShader(id);
				}

				GLOP_CORE_WARN("SHADER PROGRAM LINKING FAILED\n{0}", info_log.data());

				return;
			}

			for (GLenum id : shader_ids) {
				glDetachShader(m_id, id);
			}
		}
	}
}
