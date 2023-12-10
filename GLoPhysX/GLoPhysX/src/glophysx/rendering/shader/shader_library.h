#pragma once

#include "glophysx/core/core.h"
#include "glophysx/rendering/shader/shader.h"

namespace GLOPHYSX {

	namespace RENDERING {

		class ShaderLibrary
		{

		public:
			void Add(const Shared<Shader> shader);
			void Add(const std::string& shader_name, const Shared<Shader> shader);
			
			void Load(const std::string& file_path);
			void Load(const std::string& shader_name, const std::string& file_path);

			Shared<Shader> Get(const std::string& shader_name);

			bool Exists(const std::string& shader_name) const;

		private:
			std::unordered_map<std::string, Shared<Shader>> m_shaders;
		};
	}
}
