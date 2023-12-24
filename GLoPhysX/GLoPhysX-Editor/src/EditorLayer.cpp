#include "EditorLayer.h"

#include "glophysx/components/scene/scene_serializer.h"
#include "glophysx/core/utils/platform_utils.h"

#include "ImGuizmo.h"

#include "gtc/type_ptr.hpp"
#include "math/utils.h"

EditorLayer::EditorLayer() : Layer("EditorLayer")
{
    m_viewport_size = glm::vec2(1600.0f, 900.0f);
}

void EditorLayer::OnAttach()
{	
	GLOP_PROFILE_FUNCTION();

    FramebufferSpecs fb_specs;
    fb_specs.width = (uint32_t)m_viewport_size.x;
    fb_specs.height = (uint32_t)m_viewport_size.y;
    fb_specs.attachments = { FramebufferTextureFormat::RGBA8, FramebufferTextureFormat::RED_INTEGER, FramebufferTextureFormat::Depth };
    m_framebuffer = Framebuffer::Create(fb_specs);

    m_current_scene = MakeShared<Scene>();
    m_editor_ui.Initialize(m_current_scene);

    m_editor_camera = EditorCamera(30.0f, 1.778f, 0.1f, 1000.0f);
}

void EditorLayer::OnDetach()
{
	GLOP_PROFILE_FUNCTION();
}

void EditorLayer::OnUpdate(DeltaTime dt)
{
	GLOP_PROFILE_FUNCTION();

    FramebufferSpecs spec = m_framebuffer->GetSpecs();
    if (m_viewport_size.x > 0.f && m_viewport_size.y > 0.0f && (m_viewport_size.x != spec.width || m_viewport_size.y != spec.height)) {
        m_framebuffer->Resize((uint32_t)m_viewport_size.x, (uint32_t)m_viewport_size.y);
        m_current_scene->OnViewportResize((uint32_t)m_viewport_size.x, (uint32_t)m_viewport_size.y);
        m_editor_camera.SetViewportSize(m_viewport_size.x, m_viewport_size.y);
    }

    if (m_viewport_focused)
    {
        m_editor_camera.OnUpdate(dt);
    }

	Renderer2D::ResetStats();

	{
		GLOP_PROFILE_SCOPE("Renderer commands");
        m_framebuffer->Bind();

		RendererCommands::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
		RendererCommands::Clear();
	}

	{
		GLOP_PROFILE_SCOPE("Render draw");

        m_framebuffer->ClearAttachment(1, (const void*)(-1));

        m_current_scene->OnUpdateEditor(dt, m_editor_camera);

        auto [mx, my] = ImGui::GetMousePos();
        mx -= m_viewport_bounds[0].x;
        my -= m_viewport_bounds[0].y;
        auto viewport_width = m_viewport_bounds[1].x - m_viewport_bounds[0].x;
        auto viewport_height = m_viewport_bounds[1].y - m_viewport_bounds[0].y;
        my = viewport_height - my;

        int mouse_x = (int)mx;
        int mouse_y = (int)my;

        if (mouse_x >= 0 && mouse_y >= 0 && mouse_x < (int)viewport_width && mouse_y < (int)viewport_height)
        {
            m_selected_entity = m_framebuffer->ReadPixel(1, mouse_x, mouse_y);
        }

        m_framebuffer->Unbind();
	}
}

void EditorLayer::OnGUIRender()
{
	GLOP_PROFILE_FUNCTION();

    Application::GetInstance().GetGUILayer()->BeginDocking();

    // New, Open, Save As etc.
    FileHandler();

    // Panels
    m_editor_ui.OnGUIRender();

    // Renderer Stats
    auto& stats = Renderer2D::GetStats();
    m_editor_ui.ShowStats(stats);

    // Scene Viewport
    m_editor_ui.BeginViewport();


    m_viewport_focused = ImGui::IsWindowFocused();
    m_viewport_hovered = ImGui::IsWindowHovered();
    Application::GetInstance().GetGUILayer()->SetConsumeEvents(!m_viewport_focused && !m_viewport_hovered);

    ImVec2 viewport_panel_size = ImGui::GetContentRegionAvail();
    if (m_viewport_size != *((glm::vec2*)&viewport_panel_size)) {
        m_viewport_size.x = viewport_panel_size.x;
        m_viewport_size.y = viewport_panel_size.y;
    }

    uint32_t texture_id = m_framebuffer->GetColorAttachmentId(0);
    ImGui::Image((void*)(UINT_PTR)texture_id, ImVec2{m_viewport_size.x, m_viewport_size.y}, ImVec2{0, 1}, ImVec2{1, 0});

    auto viweport_offset = ImGui::GetWindowPos();
    auto viewport_min_region = ImGui::GetWindowContentRegionMin();
    auto viewport_max_region = ImGui::GetWindowContentRegionMax();

    m_viewport_bounds[0] = { viewport_min_region.x + viweport_offset.x, viewport_min_region.y + viweport_offset.y };
    m_viewport_bounds[1] = { viewport_max_region.x + viweport_offset.x, viewport_max_region.y + viweport_offset.y };

    // Gizmos
    ShowGizmos();

    m_editor_ui.EndViewport();

    Application::GetInstance().GetGUILayer()->EndDocking();
}

void EditorLayer::OnEvent(Event& e)
{
    if (!ImGuizmo::IsUsing())
    {
        m_editor_camera.OnEvent(e);
    }

    EventDispatcher::Dispatch<KeyPressEvent>(e, std::bind(&EditorLayer::OnKeyPress, this, std::placeholders::_1));
    EventDispatcher::Dispatch<MouseButtonPressEvent>(e, std::bind(&EditorLayer::OnMouseButtonPress, this, std::placeholders::_1));
}

void EditorLayer::FileHandler()
{
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("New", "Ctrl+N"))
            {
                NewScene();
            }

            if (ImGui::MenuItem("Open...", "Ctrl+O"))
            {
                LoadScene();
            }

            if (ImGui::MenuItem("Save", "Ctrl+S"))
            {
                SaveScene();
            }

            if (ImGui::MenuItem("Save As...", "Ctr+Shift+S"))
            {
                SaveAsScene();
            }
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }
}

void EditorLayer::NewScene()
{
    m_current_scene = MakeShared<Scene>();
    m_current_scene->OnViewportResize((uint32_t)m_viewport_size.x, (uint32_t)m_viewport_size.y);
    m_editor_ui.Initialize(m_current_scene);
}

void EditorLayer::LoadScene()
{
    std::string file_path = PLATFORM::FileDialogs::OpenFile("GLOP Scene (*.glop)\0*.glop\0");

    if (!file_path.empty())
    {
        std::string scene_name = file_path.substr(file_path.find_last_of("/\\") + 1);
        m_current_scene = MakeShared<Scene>();
        m_current_scene->SetSceneName(scene_name);
        m_current_scene->OnViewportResize((uint32_t)m_viewport_size.x, (uint32_t)m_viewport_size.y);
        m_editor_ui.Initialize(m_current_scene);

        SceneSerializer serializer(m_current_scene);
        serializer.Deserialize(file_path);
    }
}

void EditorLayer::SaveScene()
{
    if (m_current_scene != nullptr)
    {
        if (m_current_scene->GetSceneName() == "Untitled")
        {
            SaveAsScene();
        }
        else
        {
            SceneSerializer serializer(m_current_scene);
            serializer.Serialize(m_save_path + "/" + m_current_scene->GetSceneName());
        }
    }
}

void EditorLayer::SaveAsScene()
{
    std::string file_path = PLATFORM::FileDialogs::SaveFile("GLOP Scene (*.glop)\0*.glop\0");

    if (!file_path.empty())
    {
        std::string scene_name = file_path.substr(file_path.find_last_of("/\\") + 1);
        m_current_scene->SetSceneName(scene_name);
        SceneSerializer serializer(m_current_scene);
        serializer.Serialize(file_path);
    }
}

void EditorLayer::ShowGizmos()
{
    Entity m_selected_entity = m_editor_ui.m_ui_scene_hierarchy->GetSelectedContext();
    if (m_selected_entity && m_gizmo_type != -1)
    {
        ImGuizmo::SetOrthographic(false);
        ImGuizmo::SetDrawlist();

        float window_width = (float)ImGui::GetWindowWidth();
        float window_height = (float)ImGui::GetWindowHeight();

        ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, window_width, window_height);

        const glm::mat4& camera_projection = m_editor_camera.GetProjectionMatrix();
        glm::mat4 camera_view = m_editor_camera.GetViewMatrix();

        auto& tc = m_selected_entity.GetComponent<TransformComponent>();
        glm::mat4 transform = tc.GetTransform();

        bool snaping = Input::IsKeyPressed(GLOP_KEY_LEFT_CONTROL);
        float snap = 0.5f;

        if (m_gizmo_type == ImGuizmo::OPERATION::ROTATE)
        {
            snap = 45.f;
        }

        float snap_values[3] = { snap, snap, snap };

        ImGuizmo::Manipulate(glm::value_ptr(camera_view), glm::value_ptr(camera_projection),
            (ImGuizmo::OPERATION)m_gizmo_type, ImGuizmo::LOCAL, glm::value_ptr(transform),
            nullptr, snaping ? snap_values : nullptr);


        if (ImGuizmo::IsUsing() && !Input::IsKeyPressed(GLOP_KEY_LEFT_ALT))
        {
            glm::vec3 translate, scale;
            glm::quat rotation;
            glm::vec3 skew;
            glm::vec4 perspective;

            glm::decompose(transform, scale, rotation, translate, skew, perspective);

            tc.m_translation = translate;
            tc.m_rotation = glm::eulerAngles(rotation);
            tc.m_scale = scale;
        }
    }
}

bool EditorLayer::OnKeyPress(KeyPressEvent& e)
{
    if (e.GetKeycode() == GLOP_KEY_N &&
        (Input::IsKeyPressed(GLOP_KEY_LEFT_CONTROL) || Input::IsKeyPressed(GLOP_KEY_RIGHT_CONTROL)))
    {
        NewScene();
    }

    if (e.GetKeycode() == GLOP_KEY_O &&
        (Input::IsKeyPressed(GLOP_KEY_LEFT_CONTROL) || Input::IsKeyPressed(GLOP_KEY_RIGHT_CONTROL)))
    {
        LoadScene();
    }

    if (e.GetKeycode() == GLOP_KEY_S &&
        (Input::IsKeyPressed(GLOP_KEY_LEFT_CONTROL) || Input::IsKeyPressed(GLOP_KEY_RIGHT_CONTROL)))
    {
        SaveScene();
    }

    if (e.GetKeycode() == GLOP_KEY_S &&
        (Input::IsKeyPressed(GLOP_KEY_LEFT_CONTROL) || Input::IsKeyPressed(GLOP_KEY_RIGHT_CONTROL)) &&
        (Input::IsKeyPressed(GLOP_KEY_LEFT_SHIFT) || Input::IsKeyPressed(GLOP_KEY_RIGHT_SHIFT)))
    {
        SaveAsScene();
    }

    if (e.GetKeycode() == GLOP_KEY_Q)
    {
        m_gizmo_type = ImGuizmo::OPERATION::TRANSLATE;
    }

    if (e.GetKeycode() == GLOP_KEY_W)
    {
        m_gizmo_type = ImGuizmo::OPERATION::ROTATE;
    }

    if (e.GetKeycode() == GLOP_KEY_E)
    {
        m_gizmo_type = ImGuizmo::OPERATION::SCALE;
    }

    return false;
}

bool EditorLayer::OnMouseButtonPress(MouseButtonPressEvent& e)
{
    if (e.GetMouseButton() == GLOP_MOUSE_BUTTON_1)
    {
        if (m_selected_entity != -1 && !ImGuizmo::IsOver() && !Input::IsKeyPressed(GLOP_KEY_LEFT_ALT)) {
            m_editor_ui.m_ui_scene_hierarchy->SetSelectedContext(Entity{ (entt::entity)m_selected_entity, m_current_scene.get() });
        }
    }

    return false;
}
