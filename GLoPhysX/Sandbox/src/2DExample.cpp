#include "2DExample.h"

#include "gtc/type_ptr.hpp"

Example2D::Example2D() : Layer("Example2D")
{
	m_camera_controller = MakeShared<OrthographicCameraController>(1280.f / 720.f);
	m_shader_library = MakeUnique<ShaderLibrary>();
	m_checkerboard = Texture2D::Create("assets/textures/checkerboard.png");
}

void Example2D::OnAttach()
{	
	GLOP_PROFILE_FUNCTION();

    FramebufferSpecs fb_specs;
    fb_specs.width = 1600;
    fb_specs.height = 900;

    m_framebuffer = Framebuffer::Create(fb_specs);
}

void Example2D::OnDetach()
{
	GLOP_PROFILE_FUNCTION();
}

void Example2D::OnUpdate(DeltaTime dt)
{
	GLOP_PROFILE_FUNCTION();

	{
		GLOP_PROFILE_SCOPE("Camera update");
		m_camera_controller->OnUpdate(dt);
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

void Example2D::OnGUIRender()
{
	GLOP_PROFILE_FUNCTION();

    static bool dockingEnable = true;
    if (dockingEnable)
    {
        static bool p_open = true;
        static bool opt_fullscreen = true;
        static bool opt_padding = false;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
        // because it would be confusing to have two docking targets within each others.
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

        // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
        // and handle the pass-thru hole, so we ask Begin() to not render a background.
        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
        // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
        // all active windows docked into it will lose their parent and become undocked.
        // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
        // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
        if (!opt_padding)
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace Demo", &p_open, window_flags);
        if (!opt_padding)
            ImGui::PopStyleVar();

        if (opt_fullscreen)
            ImGui::PopStyleVar(2);

        // Submit the DockSpace
        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }

        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("Options"))
            {
                // Disabling fullscreen would allow the window to be moved to the front of other windows,
                // which we can't undo at the moment without finer window depth/z control.
                ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen);
                ImGui::MenuItem("Padding", NULL, &opt_padding);
                ImGui::Separator();

                if (ImGui::MenuItem("Flag: NoDockingOverCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_NoDockingOverCentralNode) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoDockingOverCentralNode; }
                if (ImGui::MenuItem("Flag: NoDockingSplit", "", (dockspace_flags & ImGuiDockNodeFlags_NoDockingSplit) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoDockingSplit; }
                if (ImGui::MenuItem("Flag: NoUndocking", "", (dockspace_flags & ImGuiDockNodeFlags_NoUndocking) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoUndocking; }
                if (ImGui::MenuItem("Flag: NoResize", "", (dockspace_flags & ImGuiDockNodeFlags_NoResize) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoResize; }
                if (ImGui::MenuItem("Flag: AutoHideTabBar", "", (dockspace_flags & ImGuiDockNodeFlags_AutoHideTabBar) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_AutoHideTabBar; }
                if (ImGui::MenuItem("Flag: PassthruCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) != 0, opt_fullscreen)) { dockspace_flags ^= ImGuiDockNodeFlags_PassthruCentralNode; }
                ImGui::Separator();

                if (ImGui::MenuItem("Close", NULL, false, &p_open != NULL))
                    p_open = false;
                ImGui::EndMenu();
            }

            ImGui::EndMenuBar();
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
        ImGui::Begin("Scene");
        ImGui::Image((void*)texture_id, ImVec2{1600.f, 900.f});
        ImGui::End();
    }
    else {
        auto& stats = Renderer2D::GetStats();

        ImGui::Begin("Renderer Stats");
        ImGui::Text("Draw calls: %d", stats.draw_calls);
        ImGui::Text("Quads: %d", stats.quad_count);
        ImGui::Text("Vertices: %d", stats.GetVertexCount());
        ImGui::Text("Indices: %d", stats.GetIndexCount());
        ImGui::End();

	    ImGui::Begin("Settings");
	    ImGui::ColorEdit3("Square Color", glm::value_ptr(m_square_color));
	    ImGui::End();
    }


}

void Example2D::OnEvent(Event& e)
{
	m_camera_controller->OnEvent(e);
}
