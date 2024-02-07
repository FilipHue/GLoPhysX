#include "tool_bar.h"

#include "imgui.h"

class EditorLayer;

namespace GLOPHYSX {

	namespace EDITOR {

		ToolBar::ToolBar()
		{
			m_play_icon = Texture2D::Create("resources/icons/play_button.png");
			m_pause_icon = Texture2D::Create("resources/icons/pause_button.png");
			m_stop_icon = Texture2D::Create("resources/icons/stop_button.png");
		}

		void ToolBar::SetContext(Shared<Scene>& context)
		{
			m_context = context;
		}

		void ToolBar::Render()
		{
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 2));
			ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(0, 2));
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.305f, 0.31f, 0.5f));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.15f, 0.152f, 0.152f, 0.5f));

			ImGui::Begin("##toolbar", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

			float size = ImGui::GetWindowHeight() - 4.0f;
			Shared<Texture2D> icon = m_scene_state == SceneState::EDIT ? m_play_icon : m_stop_icon;
			ImGui::SameLine(ImGui::GetWindowContentRegionMax().x * 0.5f - size * 0.5f);
			if (ImGui::ImageButton((ImTextureID)(UINT_PTR)icon->GetID(), ImVec2{ size, size }, ImVec2(0, 0), ImVec2(1, 1), 0))
			{
				if (m_scene_state == SceneState::EDIT)
				{
					OnScenePlay();
				}
				else if (m_scene_state == SceneState::PLAY)
				{
					OnSceneStop();
				}
			}
			ImGui::PopStyleVar(2);
			ImGui::PopStyleColor(3);
			ImGui::End();
		}

		void ToolBar::OnScenePlay()
		{
			m_scene_state = SceneState::PLAY;
			m_context->OnRuntimeStart();
		}

		void ToolBar::OnSceneStop()
		{
			m_scene_state = SceneState::EDIT;
			m_context->OnRuntimeShutdown();
		}
	}
}
