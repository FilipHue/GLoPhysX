#pragma once

#include "glophysx/core/layers/layer.h"

namespace GLOPHYSX {

	/**
	* @class GUILayer
	* @brief Specialized layer for GUI operations within the GLoPhysX engine.
	*
	* GUILayer is a layer that provides mechanisms for GUI rendering and interaction. It acts as an interface
	* between the core application and the graphical user interface, allowing the application to manage GUI
	* elements in a structured layer. This class should be subclassed if specialized GUI behavior is needed.
	*/
	class GUILayer: public Layer
	{
	public:
		GUILayer();
		virtual ~GUILayer();

		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate(DeltaTime dt) override {};
		void OnEvent(Event& e) override;

		void OnGUIRender() override;

		void Begin();
		void End();

		void BeginDocking();
		void EndDocking();

		void SetConsumeEvents(bool consume) { m_consume_events = consume; }

	private:
		void SetDarkTheme();

	private:
		bool m_consume_events = true;
	};
}
