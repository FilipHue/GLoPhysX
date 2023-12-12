#include "2DExample.h"

#include "gtc/type_ptr.hpp"

Example2D::Example2D() : Layer("Example2D")
{
	m_camera_controller = MakeShared<OrthographicCameraController>(1280.f / 720.f);
	m_shader_library = MakeUnique<ShaderLibrary>();
}

void Example2D::OnAttach()
{	
	std::vector<float> sq_vertices = {
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

	m_checkerboard = Texture2D::Create("assets/textures/checkerboard.png");

	m_shader_library->Load("assets/shaders/texture_color.glsl");
	m_shader_library->Load("assets/shaders/texture.glsl");
}

void Example2D::OnDetach()
{
}

void Example2D::OnUpdate(DeltaTime dt)
{
	m_camera_controller->OnUpdate(dt);

	RendererCommands::SetClearColor();
	RendererCommands::Clear();

	Renderer::BeginScene(MakeShared<OrthographicCamera>(m_camera_controller->GetCamera()));

	glm::mat4 model_matrix = glm::mat4(1.f);

	auto m_shader = m_shader_library->Get("texture_color");
	m_shader->Bind();
	m_shader->SetVec3("u_color", m_square_color);
	Renderer::Submit(m_shader, m_square, model_matrix);

	Renderer::EndScene();
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
