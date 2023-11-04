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
	}

	void Application::Run()
	{
		while (m_running)
		{
			glClearColor(1, 1, 0, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_window->Update();
		}
	}
	void Application::OnWindowClose(Event& e)
	{
		m_running = false;
	}
}