#pragma once

#include "scene.h"

#include "yaml-cpp/yaml.h"
#include "glm.hpp"

namespace GLOPHYSX {

	namespace COMPONENTS {

		class SceneSerializer
		{
		public:
			SceneSerializer(const Shared<Scene>& scene);

			void Serialize(const std::string& file_path);
			void SerializeRuntime(const std::string& file_path);

			bool Deserialize(const std::string& file_path);
			bool DeserializeRuntime(const std::string& file_path);

		private:
			Shared<Scene> m_scene;
		};
	}
}
