#include "editor_ui.h"

namespace GLOPHYSX {

	namespace EDITOR {

		SceneHierarchy* EditorUI::m_ui_scene_hierarchy = new SceneHierarchy();
		ContentBrowser* EditorUI::m_ui_content_browser = nullptr;
		ToolBar* EditorUI::m_ui_tool_bar = nullptr;

		void EditorUI::OnGUIRender()
		{
			m_ui_scene_hierarchy->Render();
			m_ui_entity_inspector->Render(m_ui_scene_hierarchy->GetSelectedContext());
			m_ui_content_browser->Render();
			m_ui_tool_bar->Render();
		}

		void EditorUI::Initialize(Shared<Scene>& current_scene)
		{
			m_ui_scene_hierarchy->SetContext(current_scene);
			m_ui_content_browser = new ContentBrowser();
			m_ui_tool_bar = new ToolBar();
			m_ui_tool_bar->SetContext(current_scene);
		}

		void EditorUI::Shutdown()
		{
		}

		void EditorUI::SetContext(Shared<Scene>& current_scene)
		{
			m_ui_scene_hierarchy->SetContext(current_scene);
			m_ui_tool_bar->SetContext(current_scene);
		}

		void EditorUI::BeginViewport()
		{
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
			ImGui::Begin("Viewport");
		}

		void EditorUI::EndViewport()
		{
			ImGui::End();
			ImGui::PopStyleVar();
		}

		void EditorUI::ShowStats(Statistics stats)
		{
			ImGui::Begin("Renderer Stats");
			ImGui::Text("Draw calls: %d", stats.draw_calls);
			ImGui::Text("Quads: %d", stats.quad_count);
			ImGui::Text("Vertices: %d", stats.GetVertexCount());
			ImGui::Text("Indices: %d", stats.GetIndexCount());
			ImGui::End();
		}
	}
}
