#include "gxpch.h"
#include "shader_library.h"

namespace GLOPHYSX {

	namespace RENDERING {
		void ShaderLibrary::Add(const Shared<Shader> shader)
		{
			std::string& name = shader->GetName();
			if (m_shaders.find(name) != m_shaders.end()) {
				m_shaders[name] = shader;
			}
		}
		void ShaderLibrary::Add(const std::string& shader_name, const Shared<Shader> shader)
		{
			if (m_shaders.find(shader_name) != m_shaders.end()) {
				m_shaders[shader_name] = shader;
			}
		}
		void ShaderLibrary::Load(const std::string& file_path)
		{
			auto shader = Shader::Create(file_path);
			std::string& name = shader->GetName();
			m_shaders[name] = shader;
		}
		void ShaderLibrary::Load(const std::string& shader_name, const std::string& file_path)
		{
			if (m_shaders.find(shader_name) != m_shaders.end()) {
				auto shader = Shader::Create(file_path);
				m_shaders[shader_name] = shader;
			}
		}
		Shared<Shader> ShaderLibrary::Get(const std::string& shader_name)
		{
			return m_shaders[shader_name];
		}
		bool ShaderLibrary::Exists(const std::string& shader_name) const
		{
			return m_shaders.find(shader_name) == m_shaders.end();
		}
	}
}
