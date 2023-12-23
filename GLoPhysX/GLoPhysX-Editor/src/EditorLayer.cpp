#include "EditorLayer.h"

#include "gtc/type_ptr.hpp"

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

    m_square_entity = m_current_scene->CreateEntity("Square");
    m_square_entity.AddComponent<SpriteComponent>(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));

    m_main_camera_entity = m_current_scene->CreateEntity("Main Camera");
    m_main_camera_entity.AddComponent<CameraComponent>();

    m_second_camera_entity = m_current_scene->CreateEntity("Second Camera");
    m_second_camera_entity.AddComponent<CameraComponent>();
    m_second_camera_entity.GetComponent<CameraComponent>().is_primary = false;

    m_editor_ui.Initialize(m_current_scene);

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
    Application::GetInstance().GetGUILayer()->SetConsumeEvents(!m_viewport_focused || !m_viewport_hovered);
    ImVec2 viewport_panel_size = ImGui::GetContentRegionAvail();
    if (m_viewport_size != *((glm::vec2*)&viewport_panel_size)) {
        m_viewport_size.x = viewport_panel_size.x;
        m_viewport_size.y = viewport_panel_size.y;
    }
    ImGui::Image((void*)(UINT_PTR)texture_id, ImVec2{m_viewport_size.x, m_viewport_size.y}, ImVec2{0, 1}, ImVec2{1, 0});
    ImGui::End();
    ImGui::PopStyleVar();

    Application::GetInstance().GetGUILayer()->EndDocking();
}

void EditorLayer::OnEvent(Event& e)
{
}
