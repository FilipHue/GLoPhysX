#include "gxpch.h"
#include "shader_library.h"

#ifdef GLOP_DEBUG
	#include "glophysx/debug/debug.h"
#endif

namespace GLOPHYSX {

	namespace RENDERING {

		void ShaderLibrary::Add(const Shared<Shader> shader)
		{
			GLOP_PROFILE_FUNCTION();

			std::string& name = shader->GetName();
			if (m_shaders.find(name) != m_shaders.end()) {
				m_shaders[name] = shader;
			}
		}

		void ShaderLibrary::Add(const std::string& shader_name, const Shared<Shader> shader)
		{
			GLOP_PROFILE_FUNCTION();

			if (m_shaders.find(shader_name) != m_shaders.end()) {
				m_shaders[shader_name] = shader;
			}
		}

		void ShaderLibrary::Load(const std::string& file_path)
		{
			GLOP_PROFILE_FUNCTION();

			auto shader = Shader::Create(file_path);
			std::string& name = shader->GetName();
			m_shaders[name] = shader;
		}

		void ShaderLibrary::Load(const std::string& shader_name, const std::string& file_path)
		{
			GLOP_PROFILE_FUNCTION();

			if (m_shaders.find(shader_name) != m_shaders.end()) {
				auto shader = Shader::Create(file_path);
				m_shaders[shader_name] = shader;
			}
		}

		Shared<Shader> ShaderLibrary::Get(const std::string& shader_name)
		{
			GLOP_PROFILE_FUNCTION();

			return m_shaders[shader_name];
		}

		bool ShaderLibrary::Exists(const std::string& shader_name) const
		{
			GLOP_PROFILE_FUNCTION();

			return m_shaders.find(shader_name) == m_shaders.end();
		}
	}
}
