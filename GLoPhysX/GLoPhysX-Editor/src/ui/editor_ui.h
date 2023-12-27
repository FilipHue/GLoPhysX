#pragma once

#include "glophysx.h"

#include "panels/scene_hierarchy.h"
#include "panels/entity_inspector.h"
#include "panels/content_browser.h"
#include "toolbar/tool_bar.h"

class EditorLayer;

namespace GLOPHYSX {

	namespace EDITOR {

		class EditorUI
		{
		public:
			void OnGUIRender();

			void Initialize(Shared<Scene>& current_scene);
			void Shutdown();
			void SetContext(Shared<Scene>& current_scene);

			void BeginViewport();
			void EndViewport();

		private:
			void ShowStats(Statistics stats);

		private:
			static SceneHierarchy* m_ui_scene_hierarchy;
			static EntityInspector* m_ui_entity_inspector;
			static ContentBrowser* m_ui_content_browser;
			static ToolBar* m_ui_tool_bar;

			friend class EditorLayer;
		};
	}
}
