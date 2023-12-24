#pragma once

#include "glophysx.h"
#include "panels/scene_hierarchy.h"
#include "panels/entity_inspector.h"

class EditorLayer;

namespace GLOPHYSX {

	namespace EDITOR {

		class EditorUI
		{
		public:
			static void OnGUIRender();

			static void Initialize(Shared<Scene>& current_scene);
			static void Shutdown();

			void BeginViewport();
			void EndViewport();

		private:
			void ShowStats(Statistics stats);

		private:
			static SceneHierarchy* m_ui_scene_hierarchy;
			static EntityInspector* m_ui_entity_inspector;

			friend class EditorLayer;
		};
	}
}
