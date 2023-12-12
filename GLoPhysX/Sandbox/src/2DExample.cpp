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
}

void Example2D::OnDetach()
{
}

void Example2D::OnUpdate(DeltaTime dt)
{
	GLOP_PROFILE_FUNCTION();

	{
		GLOP_PROFILE_SCOPE("Camera update");
		m_camera_controller->OnUpdate(dt);
	}

	{
		GLOP_PROFILE_SCOPE("Renderer commands");

		RendererCommands::SetClearColor();
		RendererCommands::Clear();
	}

	{
		GLOP_PROFILE_SCOPE("Begin Scene");

		Renderer2D::BeginScene(m_camera_controller->GetCamera());
	}

	{
		GLOP_PROFILE_SCOPE("Draw commands");

		Renderer2D::DrawQuad({ -1.f, 0.5f }, { 0.7f, 0.3f }, m_square_color);
		Renderer2D::DrawQuad({ 0.f, 0.f }, { 0.5f, 0.5f }, m_square_color);
		Renderer2D::DrawQuad({ 1.f, 0.5f }, { 0.7f, 0.3f }, m_square_color);

		Renderer2D::DrawQuad({ 0.f, 0.0f, -0.1f }, { 10.f, 10.f }, m_checkerboard);
	}

	{
		GLOP_PROFILE_SCOPE("End Scene");

		Renderer2D::EndScene();
	}
}

void Example2D::OnGUIRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit3("Square Color", glm::value_ptr(m_square_color));
	ImGui::End();
}

void Example2D::OnEvent(Event& e)
{
	m_camera_controller->OnEvent(e);
}
