#include "gxpch.h"

#include "application.h"

namespace GLOPHYSX {
	Application::Application()
	{
		#ifdef GLOP_PLATFORM_WINDOWS
			m_window = Window::Create<WWindow>(new WindowProperties());
			m_window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
		#else
			#error "GLoPhysX only supports Windows!"
		#endif
		m_running = true;
	}

	Application::~Application()
	{
	}

	void Application::OnEvent(Event& e)
	{	
		EventDispatcher::Dispatch<WindowCloseEvent>(e, std::bind(&Application::OnWindowClose, this, std::placeholders::_1));

		GLOP_CORE_TRACE("{0}", e.ToString());

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
			glClearColor(1, 1, 0, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : m_layers_container) {
				layer->OnUpdate();
			}

			m_window->Update();
		}
	}
	bool Application::OnWindowClose(Event& e)
	{
		m_running = false;

		return true;
	}
}