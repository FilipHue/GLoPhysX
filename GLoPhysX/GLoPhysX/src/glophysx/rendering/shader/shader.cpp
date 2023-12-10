#include "gxpch.h"
#include "shader.h"

#include "glophysx/rendering/renderer/api/renderer_api.h"
#include "glophysx/rendering/shader/platforms/opengl/opengl_shader.h"

namespace GLOPHYSX {

	namespace RENDERING {

		Shared<Shader> Shader::Create(const std::string& file_path)
		{
			switch (RendererAPI::GetApi())
			{
			case API::NONE:
				GLOP_CORE_CRITICAL("Please specify a rendering API")
					return nullptr;
			case API::OPENGL:
				return MakeShared<OpenglShader>(file_path);
			default:
				break;
			}

			GLOP_CORE_CRITICAL("Unknown rendering API")
				return nullptr;
		}
		Shared<Shader> Shader::Create(const std::string& name, std::string& source_vs, std::string& source_fs)
		{
			switch (RendererAPI::GetApi())
			{
			case API::NONE:
				GLOP_CORE_CRITICAL("Please specify a rendering API")
				return nullptr;
			case API::OPENGL:
				return MakeShared<OpenglShader>(name, source_vs, source_fs);
			default:
				break;
			}

			GLOP_CORE_CRITICAL("Unknown rendering API")
				return nullptr;
		}
		std::string Shader::ReadShaderSource(const std::string& file_path)
		{
			std::string source;
			std::ifstream in(file_path, std::ios::in | std::ios::binary);

			if (in) {
				in.seekg(0, std::ios::end);
				source.resize(in.tellg());
				in.seekg(0, std::ios::beg);
				in.read(&source[0], source.size());
				in.close();
			}
			else {
				GLOP_CORE_WARN("Couldnt open file: {0}", source);
				exit(-1);
			}

			return source;
		}
		std::unordered_map<ShaderType, std::string> Shader::ProcessShaderSource(const std::string& source)
		{
			std::unordered_map<ShaderType, std::string> shader_sources;

			const char* type_token = "type";

			size_t type_token_length = strlen(type_token);
			size_t position = source.find(type_token, 0);

			while (position != std::string::npos) {
				size_t eol = source.find_first_of("\r\n", position);

				size_t begin = position + type_token_length + 1;
				std::string type = source.substr(begin, eol - begin);

				size_t next_position = source.find_first_not_of("\r\n", eol);
				position = source.find(type_token, next_position);
				shader_sources[ShaderTypeFromString(type)] =
					source.substr(
						next_position,
						position - (next_position == std::string::npos ? source.size() - 1 : next_position)
					);
			}

			return shader_sources;
		}
	}
}
