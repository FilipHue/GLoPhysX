#pragma once

#include "glophysx/core/core.h"

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
		~GUILayer();

		void OnAtach() override;
		void OnDetach() override;
		void OnUpdate() override {};
		void OnEvent(Event& e) override;

		void OnGUIRender() override;

		void Begin();
		void End();
	};
}
