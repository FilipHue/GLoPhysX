#include <iostream>

#include "glophysx.h"

using namespace GLOPHYSX;
using namespace RENDERER;

class ExampleLayer : public Layer {
public:
	ExampleLayer() : Layer("Example") {
		// Triangle
		m_tr_vertex_array = VertexArray::Create();

		float tr_vertices[9] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f
		};
		unsigned int tr_indices[3] = { 0, 1, 2 };

		m_tr_vertex_buffer = VertexBuffer::Create(tr_vertices, sizeof(tr_vertices));
		m_tr_index_buffer = IndexBuffer::Create(tr_indices, sizeof(tr_indices) / sizeof(uint32_t));

		BufferLayout tr_layout = {
			{ShaderDataType::Float3, "a_position"}
		};
		m_tr_vertex_buffer->SetLayout(tr_layout);

		m_tr_vertex_array->AddVertexBuffer(m_tr_vertex_buffer);
		m_tr_vertex_array->AddIndexBuffer(m_tr_index_buffer);

		// Square
		m_sq_vertex_array = VertexArray::Create();

		float sq_vertices[12] = {
			-0.75f, -0.75f, 0.0f,
			0.75f, -0.75f, 0.0f,
			0.75f, 0.75f, 0.0f,
			-0.75f, 0.75f, 0.0f
		};
		unsigned int sq_indices[6] = { 0, 1, 2, 2, 3, 0 };

		m_sq_vertex_buffer = VertexBuffer::Create(sq_vertices, sizeof(sq_vertices));
		m_sq_index_buffer = IndexBuffer::Create(sq_indices, sizeof(sq_indices) / sizeof(uint32_t));

		BufferLayout sq_layout = {
			{ShaderDataType::Float3, "a_position"}
		};
		m_sq_vertex_buffer->SetLayout(sq_layout);

		m_sq_vertex_array->AddVertexBuffer(m_sq_vertex_buffer);
		m_sq_vertex_array->AddIndexBuffer(m_sq_index_buffer);
	}

	void OnUpdate() override {
		RendererCommands::SetClearColor();
		RendererCommands::Clear();

		Renderer::BeginScene();

		Renderer::Submit(m_tr_vertex_array);
		Renderer::Submit(m_sq_vertex_array);

		Renderer::EndScene();
	}

	void OnEvent(Event& e) override {

	}

private:
	std::shared_ptr<VertexArray> m_tr_vertex_array;
	std::shared_ptr<VertexBuffer> m_tr_vertex_buffer;
	std::shared_ptr<IndexBuffer> m_tr_index_buffer;

	std::shared_ptr<VertexArray> m_sq_vertex_array;
	std::shared_ptr<VertexBuffer> m_sq_vertex_buffer;
	std::shared_ptr<IndexBuffer> m_sq_index_buffer;
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
