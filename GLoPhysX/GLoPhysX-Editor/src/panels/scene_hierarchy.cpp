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
			m_contex = scene;
		}

		void SceneHierarchy::OnGUIRender()
		{

			ImGui::Begin("Scene Hierarchy");

			m_contex->m_registry.each([&](auto entity_id)
				{
					Entity entity{ entity_id, m_contex.get() };
					auto& tc = entity.GetComponent<TagComponent>();
					ImGui::Text("%s", tc.m_tag.c_str());
				});

			ImGui::End();
		}
	}
}
