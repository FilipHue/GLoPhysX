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
	/*std::vector<float> sq_vertices = {
				-0.75f, -0.75f, 0.0f,	0.f, 0.f,
				 0.75f, -0.75f, 0.0f,	1.f, 0.f,
				 0.75f,  0.75f, 0.0f,	1.f, 1.f,
				-0.75f,  0.75f, 0.0f,	0.f, 1.f
	};
	std::vector<unsigned int> sq_indices = { 0, 1, 2, 2, 3, 0 };
	BufferLayout sq_layout = {
		{ShaderDataType::Float3, "a_position"},
		{ShaderDataType::Float2, "a_texcoord"}
	};

	m_square = MakeUnique<Mesh>(sq_vertices, sq_indices, sq_layout);

	m_shader_library->Load("assets/shaders/texture_color.glsl");
	m_shader_library->Load("assets/shaders/texture.glsl");*/
}

void Example2D::OnDetach()
{
}

void Example2D::OnUpdate(DeltaTime dt)
{
	m_camera_controller->OnUpdate(dt);

	RendererCommands::SetClearColor();
	RendererCommands::Clear();

	Renderer2D::BeginScene(m_camera_controller->GetCamera());

	Renderer2D::DrawQuad({ -1.f, 0.5f }, { 0.7f, 0.3f }, m_square_color);
	Renderer2D::DrawQuad({ 0.f, 0.f }, { 0.5f, 0.5f }, m_square_color);
	Renderer2D::DrawQuad({ 1.f, 0.5f }, { 0.7f, 0.3f }, m_square_color);

	Renderer2D::DrawQuad({ 0.f, 0.0f, -0.1f }, { 10.f, 10.f }, m_checkerboard);

	Renderer2D::EndScene();
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
