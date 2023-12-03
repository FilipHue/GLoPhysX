#include "gxpch.h"

#include "application.h"

#include "glophysx/rendering/renderer/renderer.h"

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
			float current_time = (float)glfwGetTime();
			m_dt = current_time - m_previous_time;
			m_previous_time = current_time;

			for (Layer* layer : m_layers_container) {
				layer->OnUpdate(m_dt);
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
