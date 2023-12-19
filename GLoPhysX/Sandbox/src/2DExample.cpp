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
	}
}

void Example2D::OnGUIRender()
{
	GLOP_PROFILE_FUNCTION();

	auto stats = Renderer2D::GetStats();

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

void Example2D::OnEvent(Event& e)
{
	m_camera_controller->OnEvent(e);
}
