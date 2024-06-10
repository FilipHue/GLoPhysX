#pragma once

#include "glophysx.h"

#include "imgui.h"
#include "imgui_internal.h"
#include "gtc/type_ptr.hpp"

namespace GLOPHYSX {

	namespace EDITOR {

		class EntityInspector
		{
		public:
			EntityInspector() = delete;

			template<typename T, typename UIFunction>
			static void DrawComponent(const std::string& name, Entity entity, UIFunction ui_function)
			{
				if (entity.HasComponent<T>())
				{
					auto& component = entity.GetComponent<T>();
					ImVec2 content_region_avail = ImGui::GetContentRegionAvail();

					ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4, 4 });
					float line_height = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.f;
					ImGui::Separator();
					bool open = ImGui::TreeNodeEx((void*)typeid(T).hash_code(), tree_node_flags, name.c_str());
					ImGui::PopStyleVar();
					ImGui::SameLine(content_region_avail.x - line_height * 0.5f);
					if (ImGui::Button("+", ImVec2{ line_height, line_height }))
					{
						ImGui::OpenPopup("ComponentSettings");
					}

					bool to_remove = false;
					if (ImGui::BeginPopup("ComponentSettings"))
					{
						if (ImGui::MenuItem("RemoveComponent"))
						{
							to_remove = true;
						}

						ImGui::EndPopup();
					}

					if (open) {
						ui_function(component);

						ImGui::TreePop();
					}

					if (to_remove)
					{
						entity.RemoveComponent<T>();
					}
				}
			}

			template<typename T>
			void static DisplayAddComponentEntry(const std::string& entry_name, Entity& entity) {
				if (!entity.HasComponent<T>())
				{
					if (ImGui::MenuItem(entry_name.c_str()))
					{
						entity.AddComponent<T>();
						ImGui::CloseCurrentPopup();
					}
				}
			}

			static void DrawComponents(Entity& entity);

			static void DrawVec3Controls(const std::string& label, glm::vec3& value, float reset_value = 0.f, float column_width = 100.f);
			static void DrawVec2Controls(const std::string& label, glm::vec2& value, float reset_value = 0.f, float column_width = 100.f);

			static void Render(Entity& context);

		private:
			static const ImGuiTreeNodeFlags tree_node_flags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_FramePadding | ImGuiTreeNodeFlags_SpanAvailWidth;
		};
	}
}
