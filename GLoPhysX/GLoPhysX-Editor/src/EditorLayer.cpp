#include "EditorLayer.h"

#include "gtc/type_ptr.hpp"
#include "glophysx/components/scene/scene_serializer.h"
#include "glophysx/core/utils/platform_utils.h"

#include "ImGuizmo.h"

#include "math/utils.h"

EditorLayer::EditorLayer() : Layer("EditorLayer")
{
    m_viewport_size = glm::vec2(1600.0f, 900.0f);
	m_camera_controller = MakeShared<OrthographicCameraController>(m_viewport_size.x / m_viewport_size.y);
	m_shader_library = MakeUnique<ShaderLibrary>();
	m_checkerboard = Texture2D::Create("assets/textures/checkerboard.png");
}

void EditorLayer::OnAttach()
{	
	GLOP_PROFILE_FUNCTION();

    FramebufferSpecs fb_specs;
    fb_specs.width = (uint32_t)m_viewport_size.x;
    fb_specs.height = (uint32_t)m_viewport_size.y;
    m_framebuffer = Framebuffer::Create(fb_specs);

    m_current_scene = MakeShared<Scene>();
    m_editor_ui.Initialize(m_current_scene);

#if 0
    m_square_entity = m_current_scene->CreateEntity("Square");
    m_square_entity.AddComponent<SpriteComponent>(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));

    m_main_camera_entity = m_current_scene->CreateEntity("Main Camera");
    m_main_camera_entity.AddComponent<CameraComponent>();

    m_second_camera_entity = m_current_scene->CreateEntity("Second Camera");
    m_second_camera_entity.AddComponent<CameraComponent>();
    m_second_camera_entity.GetComponent<CameraComponent>().is_primary = false;

    class CameraController : public ScriptableEntity
    {
    public:
        void OnCreate() override
        {
        }

        void OnUpdate(DeltaTime dt) override
        {
            if (GetComponent<CameraComponent>().is_primary) {
                auto& translation = GetComponent<TransformComponent>().m_translation;

                if (Input::IsKeyPressed(GLOP_KEY_A)) {
                    translation.x -= m_move_speed * dt;
                }

                if (Input::IsKeyPressed(GLOP_KEY_D)) {
                    translation.x += m_move_speed * dt;
                }

                if (Input::IsKeyPressed(GLOP_KEY_S)) {
                    translation.y -= m_move_speed * dt;
                }

                if (Input::IsKeyPressed(GLOP_KEY_W)) {
                    translation.y += m_move_speed * dt;
                }
            }
        }

        void OnDestroy() override
        {
        }

    private:
        float m_move_speed = 10.f;
    };

    m_main_camera_entity.AddComponent<NativeScriptComponent>().Bind<CameraController>();
    m_second_camera_entity.AddComponent<NativeScriptComponent>().Bind<CameraController>();
#endif

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
    }

	Renderer2D::ResetStats();

	{
		GLOP_PROFILE_SCOPE("Renderer commands");
        m_framebuffer->Bind();

		RendererCommands::SetClearColor();
		RendererCommands::Clear();
	}

	{
		GLOP_PROFILE_SCOPE("Render draw");

        m_current_scene->OnUpdate(dt);

        m_framebuffer->Unbind();
	}
}

void EditorLayer::OnGUIRender()
{
	GLOP_PROFILE_FUNCTION();

    Application::GetInstance().GetGUILayer()->BeginDocking();

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

            if (ImGui::MenuItem("Save As...", "Ctr+Shift+S"))
            {
                SaveAsScene();
            }
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

    m_editor_ui.OnGUIRender();

    auto& stats = Renderer2D::GetStats();

    ImGui::Begin("Renderer Stats");
    ImGui::Text("Draw calls: %d", stats.draw_calls);
    ImGui::Text("Quads: %d", stats.quad_count);
    ImGui::Text("Vertices: %d", stats.GetVertexCount());
    ImGui::Text("Indices: %d", stats.GetIndexCount());
    ImGui::End();

    uint32_t texture_id = m_framebuffer->GetColorAttachmentId();
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
    ImGui::Begin("Viewport");
    m_viewport_focused = ImGui::IsWindowFocused();
    m_viewport_hovered = ImGui::IsWindowHovered();
    Application::GetInstance().GetGUILayer()->SetConsumeEvents(!m_viewport_focused && !m_viewport_hovered);
    ImVec2 viewport_panel_size = ImGui::GetContentRegionAvail();
    if (m_viewport_size != *((glm::vec2*)&viewport_panel_size)) {
        m_viewport_size.x = viewport_panel_size.x;
        m_viewport_size.y = viewport_panel_size.y;
    }
    ImGui::Image((void*)(UINT_PTR)texture_id, ImVec2{m_viewport_size.x, m_viewport_size.y}, ImVec2{0, 1}, ImVec2{1, 0});

    Entity selected_entity = m_editor_ui.m_ui_scene_hierarchy->GetSelectedContext();
    if (selected_entity && m_gizmo_type != -1)
    {
        ImGuizmo::SetOrthographic(false);
        ImGuizmo::SetDrawlist();

        float window_width = (float)ImGui::GetWindowWidth();
        float window_height = (float)ImGui::GetWindowHeight();

        ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, window_width, window_height);

        auto camera_entity = m_current_scene->GetPrimaryCameraEntity();
        const auto& camera = camera_entity.GetComponent<CameraComponent>().m_camera;

        const glm::mat4& camera_projection = camera.GetProjectionMatrix();
        glm::mat4 camera_view = glm::inverse(camera_entity.GetComponent<TransformComponent>().GetTransform());

        auto& tc = selected_entity.GetComponent<TransformComponent>();
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


        if (ImGuizmo::IsUsing())
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

    ImGui::End();
    ImGui::PopStyleVar();

    Application::GetInstance().GetGUILayer()->EndDocking();
}

void EditorLayer::OnEvent(Event& e)
{
    EventDispatcher::Dispatch<KeyPressEvent>(e, std::bind(&EditorLayer::OnKeyPress, this, std::placeholders::_1));
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
        m_current_scene = MakeShared<Scene>();
        m_current_scene->OnViewportResize((uint32_t)m_viewport_size.x, (uint32_t)m_viewport_size.y);
        m_editor_ui.Initialize(m_current_scene);

        SceneSerializer serializer(m_current_scene);
        serializer.Deserialize(file_path);
    }
}

void EditorLayer::SaveAsScene()
{
    std::string file_path = PLATFORM::FileDialogs::SaveFile("GLOP Scene (*.glop)\0*.glop\0");

    if (!file_path.empty())
    {
        SceneSerializer serializer(m_current_scene);
        serializer.Serialize(file_path);
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

    return true;
}
