#include "EditorLayer.h"

#include "gtc/type_ptr.hpp"

EditorLayer::EditorLayer() : Layer("EditorLayer")
{
	m_camera_controller = MakeShared<OrthographicCameraController>(1600.f / 900.f);
	m_shader_library = MakeUnique<ShaderLibrary>();
	m_checkerboard = Texture2D::Create("assets/textures/checkerboard.png");
}

void EditorLayer::OnAttach()
{	
	GLOP_PROFILE_FUNCTION();

    FramebufferSpecs fb_specs;
    fb_specs.width = 1600;
    fb_specs.height = 900;

    m_framebuffer = Framebuffer::Create(fb_specs);
}

void EditorLayer::OnDetach()
{
	GLOP_PROFILE_FUNCTION();
}

void EditorLayer::OnUpdate(DeltaTime dt)
{
	GLOP_PROFILE_FUNCTION();

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

		static float rotation = 0.f;

		rotation += dt * 20.f;

		Renderer2D::BeginScene(m_camera_controller->GetCamera());

		Renderer2D::DrawRotatedQuad({ -1.f, 0.5f }, { 0.7f, 0.3f }, rotation, m_square_color);
		Renderer2D::DrawQuad({ 0.f, 0.f }, { 0.5f, 0.5f }, m_square_color);
		Renderer2D::DrawRotatedQuad({ 1.f, 0.5f }, { 0.7f, 0.3f }, -rotation, m_square_color);

		glm::vec4 color;
		float size = 5.f;

		for (float x = -size; x < size; x += 0.5f) {
			for (float y = -size; y < size; y += 0.5f) {
				color = { (x + size) / (2 * size), (y + size) / (2 * size), 0.f, 0.7f };
				Renderer2D::DrawQuad({ x, y, -0.05f }, { 0.45f, 0.45f }, color);
			}
		}

		Renderer2D::DrawQuad({ 0.f, 0.f, -0.1f }, { 30.f, 30.f }, m_checkerboard, 10.f);

		Renderer2D::EndScene();

        m_framebuffer->Unbind();
	}
}

void EditorLayer::OnGUIRender()
{
	GLOP_PROFILE_FUNCTION();

    static bool p_open = true;
    static bool opt_fullscreen = true;
    static bool opt_padding = false;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    if (opt_fullscreen)
    {
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }
    else
    {
        dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
    }

    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
        window_flags |= ImGuiWindowFlags_NoBackground;

    if (!opt_padding)
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("DockSpace Demo", &p_open, window_flags);
    if (!opt_padding)
        ImGui::PopStyleVar();

    if (opt_fullscreen)
        ImGui::PopStyleVar(2);

    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    }

    ImGui::End();

    ImGui::Begin("Settings");
    ImGui::ColorEdit3("Square Color", glm::value_ptr(m_square_color));
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
        m_framebuffer->Resize((uint32_t)m_viewport_size.x, (uint32_t)m_viewport_size.y);

        m_camera_controller->OnViewportResize((uint32_t)m_viewport_size.x, (uint32_t)m_viewport_size.y);
    }
    ImGui::Image((void*)texture_id, ImVec2{m_viewport_size.x, m_viewport_size.y}, ImVec2{0, 1}, ImVec2{1, 0});
    ImGui::End();
    ImGui::PopStyleVar();
}

void EditorLayer::OnEvent(Event& e)
{
	m_camera_controller->OnEvent(e);
}
