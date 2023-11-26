#include "gxpch.h"

#include "application.h"

#include "glophysx/renderer/renderer/renderer.h"

namespace GLOPHYSX {

	using namespace RENDERER;

	Application* Application::s_instance = nullptr;

	Application::Application()
	{
		RendererAPI::SetApi(API::OPENGL);
		RendererCommands::SetApi();

		s_instance = this;

		#ifdef GLOP_PLATFORM_WINDOWS
			m_window = Window::Create<WWindow>(new WindowProperties());
			m_window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
			GLOP_CORE_TRACE("===========================================================================")
		#else
			#error "GLoPhysX only supports Windows!"
		#endif
		m_running = true;

		m_gui_layer = new GUILayer();
		PushOverlay(m_gui_layer);

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

	Application::~Application()
	{
	}

	void Application::OnEvent(Event& e)
	{	
		EventDispatcher::Dispatch<WindowCloseEvent>(e, std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
		EventDispatcher::Dispatch<WindowResizeEvent>(e, std::bind(&Application::OnWindowResize, this, std::placeholders::_1));

		for (auto it = m_layers_container.rbegin(); it != m_layers_container.rend(); ++it) {
			if (e.m_handled) {
				break;
			}
			(*it)->OnEvent(e);
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_layers_container.PushLayer(layer);
		layer->OnAtach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_layers_container.PushOverlay(overlay);
		overlay->OnAtach();
	}

	void Application::Run()
	{
		while (m_running)
		{
			RendererCommands::SetClearColor();
			RendererCommands::Clear();

			Renderer::BeginScene();

			Renderer::Submit(m_tr_vertex_array);
			Renderer::Submit(m_sq_vertex_array);

			Renderer::EndScene();

			for (Layer* layer : m_layers_container) {
				layer->OnUpdate();
			}

			m_gui_layer->Begin();
			for (Layer* layer : m_layers_container) {
				layer->OnGUIRender();
			}
			m_gui_layer->End();

			m_window->Update();
		}
	}
	Application& Application::GetInstance()
	{
		return *s_instance;
	}
	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_running = false;

		return true;
	}
	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}
	Window& Application::GetWindow()
	{
		return *m_window;
	}
}
