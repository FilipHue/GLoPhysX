#pragma once

#include "glophysx.h"

namespace GLOPHYSX {

	using namespace COMPONENTS;

	namespace EDITOR {

		class SceneHierarchy
		{
		public:
			SceneHierarchy() = default;
			SceneHierarchy(const Shared<Scene>& scene);

			void SetContext(const Shared<Scene>& scene);

			void OnGUIRender();

		private:
			Shared<Scene> m_contex;
		};
	}
}

