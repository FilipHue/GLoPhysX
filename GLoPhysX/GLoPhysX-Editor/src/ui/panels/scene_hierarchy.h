#pragma once

#include "glophysx.h"

namespace GLOPHYSX {

	using namespace COMPONENTS;

	namespace EDITOR {

		class SceneHierarchy
		{
		public:
			SceneHierarchy() = default;
			SceneHierarchy(const Shared<Scene>& scene) { SetContext(scene); }

			void SetContext(const Shared<Scene>& scene) { m_context = scene; m_selected_context = {}; }

			Entity GetSelectedContext() const { return m_selected_context; }
			void SetSelectedContext(Entity selected_entity) { m_selected_context = selected_entity; }

			void DrawEntityNode(Entity entity);

			void Render();

		private:
			Shared<Scene> m_context;
			Entity m_selected_context;
		};
	}
}

