#include "gxpch.h"

#include "application.h"

#include "glophysx/renderer/renderer.h"

namespace GLOPHYSX {

	using namespace RENDERER;

	Application* Application::s_instance = nullptr;

	Application::Application()
	{
		RendererAPI::SetApi(API::OPENGL);

		s_instance = this;

		#ifdef GLOP_PLATFORM_WINDOWS
			m_window = Window::Create<WWindow>(new WindowProperties());
			m_window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
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
			glClearColor(1, 1, 0, 1);
			glClear(GL_COLOR_BUFFER_BIT);

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
		glViewport(0, 0, e.GetWidth(), e.GetHeight());

		return false;
	}
	Window& Application::GetWindow()
	{
		return *m_window;
	}
}