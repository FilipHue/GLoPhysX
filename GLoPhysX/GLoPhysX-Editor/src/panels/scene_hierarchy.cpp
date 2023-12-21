#include "scene_hierarchy.h"

#include "imgui.h"

namespace GLOPHYSX {

	namespace EDITOR {

		SceneHierarchy::SceneHierarchy(const Shared<Scene>& scene)
		{
			SetContext(scene);
		}

		void SceneHierarchy::SetContext(const Shared<Scene>& scene)
		{
			m_context = scene;
		}

		void SceneHierarchy::DrawEntityNode(Entity entity)
		{
			auto& tc = entity.GetComponent<TagComponent>().m_tag;

			ImGuiTreeNodeFlags flags = ((m_selected_context == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
			bool opened = ImGui::TreeNodeEx((void*)(UINT_PTR)(uint32_t)entity, flags, tc.c_str());

			if (ImGui::IsItemClicked()) {
				m_selected_context = entity;
			}

			if (opened) {
				ImGui::TreePop();
			}
		}

		void SceneHierarchy::OnGUIRender()
		{

			ImGui::Begin("Scene Hierarchy");

			m_context->m_registry.each([&](auto entity_id)
				{
					Entity entity{ entity_id, m_context.get() };
					DrawEntityNode(entity);
				});

			ImGui::End();
		}
	}
}
