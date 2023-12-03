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
			std::string tr_vertex_src = R"(
				#version 460 core

				layout(location = 0) in vec3 a_position;
				layout(location = 1) in vec3 a_color;

				uniform mat4 u_view_projection;
				uniform mat4 u_model;

				out vec3 v_color;

				void main()
				{	
					v_color = a_color;
					gl_Position = u_view_projection * u_model * vec4(a_position, 1.0);
				}
			)";

			std::string tr_fragment_src = R"(
				#version 460 core

				layout(location = 0) out vec4 color;

				in vec3 v_color;

				void main()
				{	
					color = vec4(v_color * 0.5 + 0.5, 1.0);
				}
			)";

			std::string sq_vertex_src = R"(
				#version 460 core

				layout(location = 0) in vec3 a_position;
				layout(location = 0) in vec2 a_texcoord;

				out vec2 v_texcoord;

				uniform mat4 u_view_projection;
				uniform mat4 u_model;

				void main()
				{	
					v_texcoord = a_texcoord;
					gl_Position = u_view_projection * u_model * vec4(a_position, 1.0);
				}
			)";

			std::string sq_fragment_src = R"(
				#version 460 core

				layout(location = 0) out vec4 color;

				uniform vec3 u_color;

				void main()
				{	
					color = vec4(u_color, 1.0);
				}
			)";

			std::string sq_tex_fragment_src = R"(
				#version 460 core

				layout(location = 0) out vec4 color;
				
				uniform vec3 u_color;
				uniform sampler2D u_texture;

				in vec2 v_texcoord;

				void main()
				{	
					color = texture(u_texture, v_texcoord) * vec4(u_color, 1.0);
				}
			)";

			m_shader_tr = Shader::Create(tr_vertex_src, tr_fragment_src);
			m_shader_sq = Shader::Create(sq_vertex_src, sq_fragment_src);
			m_shader_sq_tex = Shader::Create(sq_vertex_src, sq_tex_fragment_src);
		}

		m_camera = MakeShared<OrthographicCamera>(-1.6f, 1.6f, -0.9f, 0.9f);

		m_texture_1 = Texture2D::Create("assets/textures/checkerboard.png");
		m_texture_2 = Texture2D::Create("assets/textures/logo.png");

		m_shader_sq_tex->Bind();
		m_shader_sq_tex->SetInt("u_texture", 0);
	}

	void OnUpdate(DeltaTime dt) override {

		// Controls
		{
			if (Input::IsKeyPressed(GLOP_KEY_LEFT)) {
				m_camera_position.x -= m_camera_speed * dt;
			}

			if (Input::IsKeyPressed(GLOP_KEY_RIGHT)) {
				m_camera_position.x += m_camera_speed * dt;
			}

			if (Input::IsKeyPressed(GLOP_KEY_UP)) {
				m_camera_position.y += m_camera_speed * dt;
			}

			if (Input::IsKeyPressed(GLOP_KEY_DOWN)) {
				m_camera_position.y -= m_camera_speed * dt;
			}

			if (Input::IsKeyPressed(GLOP_KEY_Q)) {
				m_camera_rotation -= m_camera_rotation_speed * dt;
			}

			if (Input::IsKeyPressed(GLOP_KEY_E)) {
				m_camera_rotation += m_camera_rotation_speed * dt;
			}

			if (Input::IsKeyPressed(GLOP_KEY_A)) {
				m_sq_position.x -= m_sq_speed * dt;
			}

			if (Input::IsKeyPressed(GLOP_KEY_D)) {
				m_sq_position.x += m_sq_speed * dt;
			}

			if (Input::IsKeyPressed(GLOP_KEY_S)) {
				m_sq_position.y -= m_sq_speed * dt;
			}

			if (Input::IsKeyPressed(GLOP_KEY_W)) {
				m_sq_position.y += m_sq_speed * dt;
			}
		}

		m_camera->SetPosition(m_camera_position);
		m_camera->SetRotation(m_camera_rotation);

		RendererCommands::SetClearColor();
		RendererCommands::Clear();

		Renderer::BeginScene(m_camera);

		glm::mat4 model_matrix = glm::mat4(1.f);
		model_matrix = glm::translate(model_matrix, m_sq_position);

		m_shader_sq_tex->Bind();
		m_shader_sq_tex->SetVec3("u_color", m_sq_color);
		m_texture_1->Bind();
		Renderer::Submit(m_shader_sq_tex, m_square->GetVertexArray(), model_matrix);
		m_texture_2->Bind();
		Renderer::Submit(m_shader_sq_tex, m_square->GetVertexArray(), model_matrix);

		model_matrix = glm::mat4(1.f);

		Renderer::Submit(m_shader_tr, m_triangle->GetVertexArray(), model_matrix);

		Renderer::EndScene();
	}

	void OnEvent(Event& e) override {

	}

	void OnGUIRender() override {
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_sq_color));
		ImGui::End();
	}

private:
	Unique<Mesh> m_triangle;
	Unique<Mesh> m_square;

	Shared<Shader> m_shader_tr;
	Shared<Shader> m_shader_sq;
	Shared<Shader> m_shader_sq_tex;

	Shared<Texture2D> m_texture_1;
	Shared<Texture2D> m_texture_2;

	glm::vec3 m_sq_color = glm::vec3(1.f);
	glm::vec3 m_sq_position = glm::vec3(0.f);
	float m_sq_speed = 3.f;

	Shared<OrthographicCamera> m_camera;
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
