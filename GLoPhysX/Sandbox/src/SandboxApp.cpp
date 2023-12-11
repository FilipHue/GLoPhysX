#include <iostream>

#include "glophysx.h"

#include "gtc/type_ptr.hpp"

using namespace GLOPHYSX;
using namespace RENDERING;
using namespace COMPONENTS;

class ExampleLayer : public Layer {
public:
	ExampleLayer() : Layer("Example") {

		// Objects creation
		{
			// Triangle
			std::vector<float> tr_vertices = {
				-0.5f,	-0.5f,	0.0f,		0.5f,	0.f,	0.f,
				0.5f,	-0.5f,	0.0f,		0.f,	0.5f,	0.f,
				0.0f,	0.5f,	0.0f,		0.f,	0.f,	0.5f
			};
			std::vector<unsigned int> tr_indices = { 0, 1, 2 };
			BufferLayout tr_layout = {
				{ShaderDataType::Float3, "a_position"},
				{ShaderDataType::Float3, "a_color"}
			};

			m_triangle = MakeUnique<Mesh>(tr_vertices, tr_indices, tr_layout);

			// Square
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
		}

		// Shader creation
		{
			m_shader_tr = Shader::Create("assets/shaders/triangle.glsl");
			m_shader_sq = Shader::Create("assets/shaders/square.glsl");

			m_shader_library.Load("assets/shaders/texture.glsl");
		}

		m_camera_controller = MakeShared<OrthographicCameraController>(1280.f / 720.f);

		m_texture_1 = Texture2D::Create("assets/textures/checkerboard.png");
		m_texture_2 = Texture2D::Create("assets/textures/smileyface.png");

		m_shader_library.Get("texture")->Bind();
		m_shader_library.Get("texture")->SetInt("u_texture", 0);
	}

	void OnUpdate(DeltaTime dt) override {

		// Controls
		{
			if (Input::IsKeyPressed(GLOP_KEY_LEFT)) {
				m_sq_position.x -= m_sq_speed * dt;
			}

			if (Input::IsKeyPressed(GLOP_KEY_RIGHT)) {
				m_sq_position.x += m_sq_speed * dt;
			}

			if (Input::IsKeyPressed(GLOP_KEY_DOWN)) {
				m_sq_position.y -= m_sq_speed * dt;
			}

			if (Input::IsKeyPressed(GLOP_KEY_UP)) {
				m_sq_position.y += m_sq_speed * dt;
			}
		}

		m_camera_controller->OnUpdate(dt);

		RendererCommands::SetClearColor();
		RendererCommands::Clear();

		Renderer::BeginScene(MakeShared<OrthographicCamera>(m_camera_controller->GetCamera()));

		glm::mat4 model_matrix = glm::mat4(1.f);
		model_matrix = glm::translate(model_matrix, m_sq_position);

		auto m_shader = m_shader_library.Get("texture");
		m_shader->Bind();
		m_shader->SetVec3("u_color", m_sq_color);
		m_texture_1->Bind();
		Renderer::Submit(m_shader, m_square->GetVertexArray(), model_matrix);
		m_texture_2->Bind();
		Renderer::Submit(m_shader, m_square->GetVertexArray(), model_matrix);

		model_matrix = glm::mat4(1.f);

		Renderer::Submit(m_shader_tr, m_triangle, model_matrix);

		Renderer::EndScene();
	}

	void OnEvent(Event& e) override {
		m_camera_controller->OnEvent(e);
	}

	void OnGUIRender() override {
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_sq_color));
		ImGui::End();
	}

private:
	Unique<Mesh> m_triangle;
	Unique<Mesh> m_square;

	ShaderLibrary m_shader_library;

	Shared<Shader> m_shader_tr;
	Shared<Shader> m_shader_sq;

	Shared<Texture2D> m_texture_1;
	Shared<Texture2D> m_texture_2;

	glm::vec3 m_sq_color = glm::vec3(1.f);
	glm::vec3 m_sq_position = glm::vec3(0.f);
	float m_sq_speed = 3.f;

	Shared<OrthographicCameraController> m_camera_controller;
	glm::vec3 m_camera_position = glm::vec3(0.f);
	float m_camera_rotation = 0.f;
	float m_camera_speed = 5.f;
	float m_camera_rotation_speed = 90.f;
};

class Sandbox : public Application {
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
	}

	~Sandbox() {

	}
};

GLOPHYSX::Application* GLOPHYSX::CreateApplication() {
	return new Sandbox();
}
