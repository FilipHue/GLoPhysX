#include "EditorLayer.h"

#include "gtc/type_ptr.hpp"

EditorLayer::EditorLayer() : Layer("EditorLayer")
{
    m_viewport_size = glm::vec2(1600.f, 900.f);
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

    auto square = m_current_scene->CreateEntity("Square");
    square.AddComponent<SpriteComponent>(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
    m_square_entity = square;

    m_main_camera_entity = m_current_scene->CreateEntity("Main Camera");
    m_main_camera_entity.AddComponent<CameraComponent>();
    //m_main_camera_entity.GetComponent<TransformComponent>().m_transform = glm::translate(glm::mat4(1.f), glm::vec3(-0.5f, 0.f, 0.f));

    m_second_camera_entity = m_current_scene->CreateEntity("Second Camera");
    m_second_camera_entity.AddComponent<CameraComponent>();
    //m_second_camera_entity.GetComponent<TransformComponent>().m_transform = glm::translate(glm::mat4(1.f), glm::vec3(0.5f, 0.f, 0.f));
    m_second_camera_entity.GetComponent<CameraComponent>().is_primary = false;

    m_scene_hierarchy.SetContext(m_current_scene);

    class CameraController : public ScriptableEntity
    {
    public:
        void OnCreate() override
        {
        }

        void OnUpdate(DeltaTime dt) override
        {
            auto& transform = GetComponent<TransformComponent>().m_transform;

            if (Input::IsKeyPressed(GLOP_KEY_A)) {
                transform[3][0] -= m_move_speed * dt;
            }

            if (Input::IsKeyPressed(GLOP_KEY_D)) {
                transform[3][0] += m_move_speed * dt;
            }

            if (Input::IsKeyPressed(GLOP_KEY_S)) {
                transform[3][1] -= m_move_speed * dt;
            }

            if (Input::IsKeyPressed(GLOP_KEY_W)) {
                transform[3][1] += m_move_speed * dt;
            }

        }

        void OnDestroy() override
        {
        }

    private:
        float m_move_speed = 10.f;
    };

    m_second_camera_entity.AddComponent<NativeScriptComponent>().Bind<CameraController>();
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

	{
		GLOP_PROFILE_SCOPE("Camera update");
        if (m_viewport_focused && m_viewport_hovered) {
		    m_camera_controller->OnUpdate(dt);
        }
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

    m_scene_hierarchy.OnGUIRender();

    ImGui::Begin("Settings");
    ImGui::ColorEdit3("Square Color", glm::value_ptr(m_square_color));
    m_square_entity.GetComponent<SpriteComponent>().m_color = m_square_color;

    static bool switch_cameras = true;
    if (ImGui::Checkbox("Main Camera", &switch_cameras))
    {
        m_main_camera_entity.GetComponent<CameraComponent>().is_primary = switch_cameras;
        m_second_camera_entity.GetComponent<CameraComponent>().is_primary = !switch_cameras;
    }

    {
        auto& camera = m_second_camera_entity.GetComponent<CameraComponent>().m_camera;
        float ortho_size = camera.GetOrthographicProjectionSize();
        bool changed_size = ImGui::DragFloat("Second Camera Size", &ortho_size);
        if (changed_size) {
            camera.SetOrthographicProjectionSize(ortho_size);
        }
    }
    ImGui::End();

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
    Application::GetInstance().GetGUILayer()->SetConsumeEvents(!m_viewport_focused || !m_viewport_hovered);
    ImVec2 viewport_panel_size = ImGui::GetContentRegionAvail();
    if (m_viewport_size != *((glm::vec2*)&viewport_panel_size)) {
        m_viewport_size.x = viewport_panel_size.x;
        m_viewport_size.y = viewport_panel_size.y;
    }
    ImGui::Image((void*)texture_id, ImVec2{m_viewport_size.x, m_viewport_size.y}, ImVec2{0, 1}, ImVec2{1, 0});
    ImGui::End();
    ImGui::PopStyleVar();

    Application::GetInstance().GetGUILayer()->EndDocking();
}

void EditorLayer::OnEvent(Event& e)
{
	m_camera_controller->OnEvent(e);
}
