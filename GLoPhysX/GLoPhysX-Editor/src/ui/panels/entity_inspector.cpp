#include "entity_inspector.h"

namespace GLOPHYSX {

	namespace EDITOR {

		void EntityInspector::DrawComponents(Entity& entity)
		{
			if (entity.HasComponent<TagComponent>())
			{
				auto& tag = entity.GetComponent<TagComponent>().m_tag;

				static char buffer[512];
				memset(buffer, 0, sizeof(buffer));
				strcpy_s(buffer, sizeof(buffer), tag.c_str());
				if (ImGui::InputText("Tag", buffer, sizeof(buffer))) {
					tag = std::string(buffer);
				}
			}

			ImGui::SameLine();
			ImGui::PushItemWidth(-1);

			if (ImGui::Button("Add component"))
			{
				ImGui::OpenPopup("AddComponent");
			}

			if (ImGui::BeginPopup("AddComponent"))
			{
				if (ImGui::MenuItem("Camera"))
				{
					entity.AddComponent<CameraComponent>();
					ImGui::CloseCurrentPopup();
				}

				if (ImGui::MenuItem("Sprite"))
				{
					entity.AddComponent<SpriteComponent>();
					ImGui::CloseCurrentPopup();
				}

				ImGui::EndPopup();
			}

			ImGui::PopItemWidth();

			DrawComponent<TransformComponent>("Transform", entity, [](auto& component)
				{
					DrawVec3Controls("Translation", component.m_translation);

					glm::vec3 rotation = glm::degrees(component.m_rotation);
					DrawVec3Controls("Rotation", rotation);
					component.m_rotation = glm::radians(rotation);

					DrawVec3Controls("Scale", component.m_scale, 1.f);
				});
			DrawComponent<CameraComponent>("Camera", entity, [](auto& component)
				{
					auto& camera = component.m_camera;

					const char* projection_type_str[] = { "Perspective", "Othographic" };
					const char* current_projection_type_str = projection_type_str[(int)(camera.GetProjectionType())];
					if (ImGui::BeginCombo("Projection", current_projection_type_str))
					{
						for (int i = 0; i < 2; i++) {
							bool is_selected = current_projection_type_str == projection_type_str[i];

							if (ImGui::Selectable(projection_type_str[i], is_selected))
							{
								current_projection_type_str = projection_type_str[i];
								camera.SetProjectionType((SceneCamera::ProjectionType)i);
							}

							if (is_selected) {
								ImGui::SetItemDefaultFocus();
							}
						}

						ImGui::EndCombo();
					}

					bool primary = component.is_primary;
					if (ImGui::Checkbox("Main Camera", &primary))
					{
						component.is_primary = primary;
					}

					bool fixed_ap = component.fixed_aspect_ratio;
					if (ImGui::Checkbox("Fixed Aspect Ratio", &fixed_ap))
					{
						component.fixed_aspect_ratio = fixed_ap;
					}

					if (camera.GetProjectionType() == SceneCamera::ProjectionType::PERSPECTIVE)
					{
						float persp_fov = glm::degrees(camera.GetPerspectiveProjectionFov());
						if (ImGui::DragFloat("FOV", &persp_fov))
						{
							camera.SetPerspectiveProjectionFov(glm::radians(persp_fov));
						}

						float persp_near = camera.GetPerspectiveNearZ();
						if (ImGui::DragFloat("Near", &persp_near))
						{
							camera.SetPerspectiveNearZ(persp_near);
						}

						float persp_far = camera.GetPerspectiveFarZ();
						if (ImGui::DragFloat("Far", &persp_far))
						{
							camera.SetPerspectiveFarZ(persp_far);
						}
					}

					if (camera.GetProjectionType() == SceneCamera::ProjectionType::ORTHOGRAPHIC)
					{
						float ortho_size = camera.GetOrthographicProjectionSize();
						if (ImGui::DragFloat("Size", &ortho_size))
						{
							camera.SetOrthographicProjectionSize(ortho_size);
						}

						float ortho_near = camera.GetOrthographicNearZ();
						if (ImGui::DragFloat("Near", &ortho_near))
						{
							camera.SetOrthographicNearZ(ortho_near);
						}

						float ortho_far = camera.GetOrthographicFarZ();
						if (ImGui::DragFloat("Far", &ortho_far))
						{
							camera.SetOrthographicFarZ(ortho_far);
						}
					}
				});
			DrawComponent<SpriteComponent>("Sprite", entity, [](auto& component)
				{
					ImGui::ColorEdit4("Color", glm::value_ptr(component.m_color));
				});
		}

		void EntityInspector::DrawVec3Controls(const std::string& label, glm::vec3& value, float reset_value, float column_width)
		{
			ImGuiIO& io = ImGui::GetIO();
			auto bold_font = io.Fonts->Fonts[0];

			ImGui::PushID(label.c_str());

			ImGui::Columns(2);
			ImGui::SetColumnWidth(0, column_width);
			ImGui::Text(label.c_str());
			ImGui::NextColumn();

			ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

			float line_height = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.f;
			ImVec2 button_size = { line_height + 3.f, line_height };

			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.f });
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.f });
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.f });
			ImGui::PushFont(bold_font);
			if (ImGui::Button("X", button_size))
			{
				value.x = reset_value;
			}
			ImGui::PopFont();
			ImGui::PopStyleColor(3);

			ImGui::SameLine();
			ImGui::DragFloat("##X", &value.x, 0.1f, 0.f, 0.f, "%.2f");
			ImGui::PopItemWidth();
			ImGui::SameLine();

			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.3f, 1.f });
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.f });
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.f });
			ImGui::PushFont(bold_font);
			if (ImGui::Button("Y", button_size))
			{
				value.y = reset_value;
			}
			ImGui::PopFont();
			ImGui::PopStyleColor(3);

			ImGui::SameLine();
			ImGui::DragFloat("##Y", &value.y, 0.1f, 0.f, 0.f, "%.2f");
			ImGui::PopItemWidth();
			ImGui::SameLine();

			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.f });
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.f });
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.1f, 1.f });
			ImGui::PushFont(bold_font);
			if (ImGui::Button("Z", button_size))
			{
				value.z = reset_value;
			}
			ImGui::PopFont();
			ImGui::PopStyleColor(3);

			ImGui::SameLine();
			ImGui::DragFloat("##Z", &value.z, 0.1f, 0.f, 0.f, "%.2f");
			ImGui::PopItemWidth();

			ImGui::PopStyleVar();

			ImGui::Columns(1);

			ImGui::PopID();
		}

		void EntityInspector::Render(Entity& context)
		{
			ImGui::Begin("Inspector");

			if (context) {
				DrawComponents(context);
			}

			ImGui::End();
		}
	}
}
