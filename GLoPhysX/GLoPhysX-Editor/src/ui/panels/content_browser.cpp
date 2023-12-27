#include "content_browser.h"

#include "imgui.h"

#include <iostream>

namespace GLOPHYSX {

	namespace EDITOR {

		extern const std::filesystem::path g_assets_path = "assets";

		ContentBrowser::ContentBrowser()
		{
			m_current_directory = "assets";

			m_directory_icon = Texture2D::Create("resources/icons/directory_icon.png", 1);
			m_file_icon = Texture2D::Create("resources/icons/file_icon.png", 1);
			m_back_icon = Texture2D::Create("resources/icons/back_icon.png", 1);
		}

		void ContentBrowser::Render()
		{
			ImGui::Begin("Content Browser");

			if (m_current_directory != std::filesystem::path("assets"))
			{	
				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
				if (ImGui::ImageButton((ImTextureID)(UINT_PTR)m_back_icon->GetID(), { 16, 16 }, { 0, 1 }, { 1, 0 }))
				{
					m_current_directory = m_current_directory.parent_path();
				}
				ImGui::PopStyleColor();
			}

			float panel_width = ImGui::GetContentRegionAvail().x;
			int column_count = (int)panel_width / (int)m_cell_size;
			if (column_count < 1)
			{
				column_count = 1;
			}

			ImGui::Columns(column_count, 0, false);

			int id = 0;
			for (auto& directory_entry : std::filesystem::directory_iterator(m_current_directory))
			{
				const auto& path = directory_entry.path();
				auto relative_path = std::filesystem::relative(path, g_assets_path);
				std::string filename_string = relative_path.filename().string();
				
				Shared<Texture2D> icon = directory_entry.is_directory() ? m_directory_icon : m_file_icon;
				ImGui::PushID(filename_string.c_str());
				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
				ImGui::ImageButton((ImTextureID)(UINT_PTR)icon->GetID(), { m_thumbnail_size, m_thumbnail_size }, { 0, 1 }, { 1, 0 });
				if (ImGui::BeginDragDropSource())
				{
					const wchar_t* item_path = relative_path.c_str();
					ImGui::SetDragDropPayload("CONTENT_BROWSER_ITEM", item_path, (wcslen(item_path) + 1) * sizeof(wchar_t));

					ImGui::EndDragDropSource();
				}
				ImGui::PopStyleColor();

				if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
				{
					if (directory_entry.is_directory())
					{
						m_current_directory /= path.filename();
					}
				}
				else
				{
					ImGui::TextWrapped(filename_string.c_str());
				}

				ImGui::NextColumn();
				ImGui::PopID();
			}

			ImGui::Columns(1);

			ImGui::End();
		}
	}
}
