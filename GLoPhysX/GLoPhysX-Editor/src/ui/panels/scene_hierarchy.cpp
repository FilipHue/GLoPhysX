#include "scene_hierarchy.h"

#include "imgui.h"
#include "imgui_internal.h"

#include "gtc/type_ptr.hpp"

namespace GLOPHYSX {

	namespace EDITOR {

		void SceneHierarchy::DrawEntityNode(Entity entity)
		{
			auto& tag = entity.GetComponent<TagComponent>().m_tag;

			ImGuiTreeNodeFlags flags = ((m_selected_context == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
			flags |= ImGuiTreeNodeFlags_SpanAvailWidth;
			bool opened = ImGui::TreeNodeEx((void*)(UINT_PTR)(uint32_t)entity, flags, tag.c_str());

			if (ImGui::IsItemClicked()) {
				m_selected_context = entity;
			}

			bool entity_to_delete = false;
			if (ImGui::BeginPopupContextItem())
			{
				if (ImGui::MenuItem("Delete Entity"))
				{
					entity_to_delete = true;
				}

				ImGui::EndPopup();
			}

			if (opened) {
				ImGui::TreePop();
			}

			if (entity_to_delete) {
				m_context->DestroyEntity(entity);
				if (m_selected_context == entity)
				{
					m_selected_context = {};
				}
			}
		}

		void SceneHierarchy::Render()
		{
			ImGui::Begin("Scene Hierarchy");

			auto entities = m_context->m_registry.storage<entt::entity>().each();
			if (entities.begin() != entities.end())
			{
				for (const auto& [entity_id] : entities)
				{
					Entity entity{ entity_id, m_context.get() };
					DrawEntityNode(entity);
				}

			}

			if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
			{
				m_selected_context = {};
			}

			if (ImGui::BeginPopupContextWindow(0, ImGuiPopupFlags_MouseButtonRight | ImGuiPopupFlags_NoOpenOverItems))
			{
				if (ImGui::MenuItem("Create Empty Entity"))
				{
					m_context->CreateEntity("Empty Entity");
				}

				ImGui::EndPopup();
			}

			ImGui::End();
		}
	}
}
