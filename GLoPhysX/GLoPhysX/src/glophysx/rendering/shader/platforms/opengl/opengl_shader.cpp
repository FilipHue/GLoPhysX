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

			CreateCacheDirectoryIfNeeded();

			std::string source = ReadShaderSource(file_path);
			auto shaderSources = ProcessShaderSource(source);
			m_file_path = file_path;

			{
				CompileOrGetVulkanBinaries(shaderSources);
				CompileOrGetOpenglBinaries();
				CreateProgram();
			}

			// Extract name from filepath
			auto lastSlash = file_path.find_last_of("/\\");
			lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
			auto lastDot = file_path.rfind('.');
			auto count = lastDot == std::string::npos ? file_path.size() - lastSlash : lastDot - lastSlash;
			m_name = file_path.substr(lastSlash, count);
		}

		OpenglShader::OpenglShader(const std::string& name, std::string& source_vs, std::string& source_fs)
		{
			GLOP_PROFILE_FUNCTION();

			m_name = name;

			std::unordered_map<ShaderType, std::string> shader_sources;

			shader_sources[VERTEX] = source_vs;
			shader_sources[FRAGMENT] = source_fs;

			CompileOrGetVulkanBinaries(shader_sources);
			CompileOrGetOpenglBinaries();
			CreateProgram();
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

		// SPIRV Specific
		void OpenglShader::CompileOrGetVulkanBinaries(const std::unordered_map<ShaderType, std::string>& shader_sources)
		{
			GLuint program = glCreateProgram();

			shaderc::Compiler compiler;
			shaderc::CompileOptions options;
			options.SetTargetEnvironment(shaderc_target_env_vulkan, shaderc_env_version_vulkan_1_2);

			// BUG?: Type mismatch if we use optimization
			//options.SetOptimizationLevel(shaderc_optimization_level_performance);

			std::filesystem::path cache_directory = GetCacheDirectory();

			auto& shader_data = m_vulkan_SPIRV;
			shader_data.clear();

			for (auto&& [stage, source] : shader_sources)
			{
				std::filesystem::path shaderFilePath = m_file_path;
				std::filesystem::path cachedPath = cache_directory / (shaderFilePath.filename().string() + GLShaderStageCachedVulkanFileExtension(GetShaderType(stage)));

				std::ifstream in(cachedPath, std::ios::in | std::ios::binary);
				if (in.is_open())
				{
					in.seekg(0, std::ios::end);
					auto size = in.tellg();
					in.seekg(0, std::ios::beg);

					auto& data = shader_data[GetShaderType(stage)];
					data.resize(size / sizeof(uint32_t));
					in.read((char*)data.data(), size);
				}
				else
				{
					shaderc::SpvCompilationResult module = compiler.CompileGlslToSpv(source, GLShaderStageToShaderC(GetShaderType(stage)), m_file_path.string().c_str(), options);
					if (module.GetCompilationStatus() != shaderc_compilation_status_success)
					{
						GLOP_CORE_CRITICAL("CompileOrGetVulkanBinaries failed:\n{0}", module.GetErrorMessage());
						exit(-1);
					}

					shader_data[GetShaderType(stage)] = std::vector<uint32_t>(module.cbegin(), module.cend());

					std::ofstream out(cachedPath, std::ios::out | std::ios::binary);
					if (out.is_open())
					{
						auto& data = shader_data[GetShaderType(stage)];
						out.write((char*)data.data(), data.size() * sizeof(uint32_t));
						out.flush();
						out.close();
					}
				}
			}

			for (auto&& [stage, data] : shader_data)
				Reflect(stage, data);
		}

		void OpenglShader::CompileOrGetOpenglBinaries()
		{
			auto& shader_data = m_opengl_SPIRV;

			shaderc::Compiler compiler;
			shaderc::CompileOptions options;
			options.SetTargetEnvironment(shaderc_target_env_opengl, shaderc_env_version_opengl_4_5);

			// BUG?: Type mismatch if we use optimization
			//options.SetOptimizationLevel(shaderc_optimization_level_performance);

			std::filesystem::path cacheDirectory = GetCacheDirectory();

			shader_data.clear();
			m_opengl_source_code.clear();
			for (auto&& [stage, spirv] : m_vulkan_SPIRV)
			{
				std::filesystem::path shaderFilePath = m_file_path;
				std::filesystem::path cachedPath = cacheDirectory / (shaderFilePath.filename().string() + GLShaderStageCachedOpenGLFileExtension(stage));

				std::ifstream in(cachedPath, std::ios::in | std::ios::binary);
				if (in.is_open())
				{
					in.seekg(0, std::ios::end);
					auto size = in.tellg();
					in.seekg(0, std::ios::beg);

					auto& data = shader_data[stage];
					data.resize(size / sizeof(uint32_t));
					in.read((char*)data.data(), size);
				}
				else
				{
					spirv_cross::CompilerGLSL glslCompiler(spirv);
					m_opengl_source_code[stage] = glslCompiler.compile();
					auto& source = m_opengl_source_code[stage];

					shaderc::SpvCompilationResult module = compiler.CompileGlslToSpv(source, GLShaderStageToShaderC(stage), m_file_path.string().c_str());
					if (module.GetCompilationStatus() != shaderc_compilation_status_success)
					{
						GLOP_CORE_CRITICAL("CompileOrGetOpenglBinaries failed:\n{0}", module.GetErrorMessage());
						exit(-1);
					}

					shader_data[stage] = std::vector<uint32_t>(module.cbegin(), module.cend());

					std::ofstream out(cachedPath, std::ios::out | std::ios::binary);
					if (out.is_open())
					{
						auto& data = shader_data[stage];
						out.write((char*)data.data(), data.size() * sizeof(uint32_t));
						out.flush();
						out.close();
					}
				}
			}
		}

		void OpenglShader::CreateProgram()
		{
			GLuint program = glCreateProgram();

			std::vector<GLuint> shader_IDs;
			for (auto&& [stage, spirv] : m_opengl_SPIRV)
			{
				GLuint shader_ID = shader_IDs.emplace_back(glCreateShader(stage));
				glShaderBinary(1, &shader_ID, GL_SHADER_BINARY_FORMAT_SPIR_V, spirv.data(), (uint32_t)spirv.size() * sizeof(uint32_t));
				glSpecializeShader(shader_ID, "main", 0, nullptr, nullptr);

				GLint compiled;
				glGetShaderiv(shader_ID, GL_COMPILE_STATUS, &compiled);
				if (compiled == GL_FALSE)
				{
					GLint max_length;
					glGetProgramiv(shader_ID, GL_INFO_LOG_LENGTH, &max_length);

					std::vector<GLchar> info_log(max_length);
					glGetProgramInfoLog(shader_ID, max_length, &max_length, info_log.data());
					GLOP_CORE_CRITICAL("{0} creation failed ({1}):\n{2}", stage, m_file_path.string().c_str(), info_log.data());

					glDeleteShader(shader_ID);

					exit(-1);
				}

				glAttachShader(program, shader_ID);
			}

			glLinkProgram(program);

			GLint is_linked;
			glGetProgramiv(program, GL_LINK_STATUS, &is_linked);
			if (is_linked == GL_FALSE)
			{
				GLint max_length;
				glGetProgramiv(program, GL_INFO_LOG_LENGTH, &max_length);

				std::vector<GLchar> info_log(max_length);
				glGetProgramInfoLog(program, max_length, &max_length, info_log.data());
				GLOP_CORE_CRITICAL("Shader linking failed ({0}):\n{1}", m_file_path.string().c_str(), info_log.data());

				glDeleteProgram(program);

				for (auto id : shader_IDs)
					glDeleteShader(id);

				exit(-1);
			}

			for (auto id : shader_IDs)
			{
				glDetachShader(program, id);
				glDeleteShader(id);
			}

			m_id = program;
		}

		void OpenglShader::Reflect(GLenum stage, const std::vector<uint32_t>& shader_data)
		{
#if 0
			spirv_cross::Compiler compiler(shader_data);
			spirv_cross::ShaderResources resources = compiler.get_shader_resources();

			GLOP_CORE_TRACE("OpenGLShader::Reflect - {0} {1}", GLShaderStageToString(stage), m_file_path.string().c_str());
			GLOP_CORE_TRACE(" {0} uniform buffers", resources.uniform_buffers.size());
			GLOP_CORE_TRACE(" {0} resources", resources.sampled_images.size());

			GLOP_CORE_TRACE("Uniform buffers:");
			for (const auto& resource : resources.uniform_buffers)
			{
				const auto& bufferType = compiler.get_type(resource.base_type_id);
				uint32_t bufferSize = compiler.get_declared_struct_size(bufferType);
				uint32_t binding = compiler.get_decoration(resource.id, spv::DecorationBinding);
				int memberCount = bufferType.member_types.size();

				GLOP_CORE_TRACE(" {0}", resource.name);
				GLOP_CORE_TRACE("  Size = {0}", bufferSize);
				GLOP_CORE_TRACE("  Binding = {0}", binding);
				GLOP_CORE_TRACE("  Members = {0}", memberCount);
			}

			GLOP_CORE_TRACE("Input variables:");
			for (const auto& input : resources.stage_inputs)
			{
				const auto& type = compiler.get_type(input.base_type_id);
				GLOP_CORE_TRACE(" {0}", compiler.get_fallback_name(input.id));
				GLOP_CORE_TRACE("  Location: {0}", compiler.get_decoration(input.id, spv::DecorationLocation));
				GLOP_CORE_TRACE("  Type: {0}", GetTypeName(type));
			}

			GLOP_CORE_TRACE("Output variables:");
			for (const auto& output : resources.stage_outputs)
			{
				const auto& type = compiler.get_type(output.base_type_id);
				GLOP_CORE_TRACE(" {0}", compiler.get_fallback_name(output.id));
				GLOP_CORE_TRACE("  Location: {0}", compiler.get_decoration(output.id, spv::DecorationLocation));
				GLOP_CORE_TRACE("  Type: {0}", GetTypeName(type));
			}
#endif
			std::cout << "\n";
		}
	}
}
