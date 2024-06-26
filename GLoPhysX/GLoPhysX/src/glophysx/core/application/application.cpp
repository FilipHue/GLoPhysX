#include "gxpch.h"

#include "application.h"

#include "glophysx/rendering/renderer/renderer.h"

#ifdef GLOP_DEBUG
	#include "glophysx/debug/debug.h"
#endif

#include <filesystem>

namespace GLOPHYSX {

	using namespace RENDERING;

	Application* Application::s_instance = nullptr;

	Application::Application(const ApplicationSpecifications& specs)
	{
		GLOP_PROFILE_FUNCTION();

		m_specs = specs;
		if (!m_specs.m_working_directory.empty())
		{
			std::filesystem::current_path(m_specs.m_working_directory);
		}
		GLOP_CORE_INFO("Application created in\n{0}", m_specs.m_working_directory);

		RendererAPI::SetApi(API::OPENGL);
		RendererCommands::SetApi();

		s_instance = this;

		#ifdef GLOP_PLATFORM_WINDOWS
		m_window = Window::Create<WWindow>(new WindowProperties({m_specs.m_name.c_str(), m_specs.m_width, m_specs.m_height}));
			m_window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
			m_running = true;
			GLOP_CORE_TRACE("===========================================================================")
		#else
			#error "GLoPhysX only supports Windows!"
		#endif

		Renderer::Init();

		m_gui_layer = MakeShared<GUILayer>();
		PushOverlay(m_gui_layer);
	}

	Application::~Application()
	{
		GLOP_PROFILE_FUNCTION();

		Renderer::ShutDown();
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

	void Application::PushLayer(Shared<Layer> layer)
	{
		GLOP_PROFILE_FUNCTION();

		m_layers_container.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Shared<Layer> overlay)
	{
		GLOP_PROFILE_FUNCTION();

		m_layers_container.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void Application::Run()
	{
		GLOP_PROFILE_FUNCTION();

		while (m_running)
		{
			float current_time = (float)glfwGetTime();

			// EMA dt
			double alpha = 0.9f;
			m_dt = alpha * m_dt + (1 - alpha) * (current_time - m_previous_time);

			// Normal dt
			//m_dt = current_time - m_previous_time;
			m_previous_time = current_time;

			{
				GLOP_PROFILE_SCOPE("Layer stack: On Update");

				for (Shared<Layer>& layer : m_layers_container) {
					layer->OnUpdate(m_dt);
				}
			}

			m_gui_layer->Begin();
			{
				GLOP_PROFILE_SCOPE("Layer stack: On GUI Update");

				for (Shared<Layer>& layer : m_layers_container) {
					layer->OnGUIRender();
				}
			}
			m_gui_layer->End();

			m_window->Update();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_running = false;

		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		GLOP_PROFILE_FUNCTION();

		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}
}
