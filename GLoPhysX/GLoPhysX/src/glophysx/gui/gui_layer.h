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
		GLOP_API GUILayer();
		GLOP_API ~GUILayer();

		GLOP_API void OnAtach() override;
		GLOP_API void OnDetach() override;
		GLOP_API void OnUpdate() override {};
		GLOP_API void OnEvent(Event& e) override;

		GLOP_API void OnGUIRender() override;

		GLOP_API void Begin();
		GLOP_API void End();
	};
}


