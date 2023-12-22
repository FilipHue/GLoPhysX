#include "editor_ui.h"

namespace GLOPHYSX {

	namespace EDITOR {

		SceneHierarchy* EditorUI::m_ui_scene_hierarchy = new SceneHierarchy();

		void EditorUI::OnGUIRender()
		{
			m_ui_scene_hierarchy->Render();
			m_ui_entity_inspector->Render(m_ui_scene_hierarchy->GetSelectedContext());
		}

		void EditorUI::Initialize(Shared<Scene>& current_scene)
		{
			m_ui_scene_hierarchy->SetContext(current_scene);
		}

		void EditorUI::Shutdown()
		{
		}
	}
}
