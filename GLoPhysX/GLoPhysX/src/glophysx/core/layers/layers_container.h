#pragma once
/**
* @file LayersContainer.h
* @brief Manages layers and overlays within the GLOPHYSX engine's runtime environment.
*
* The LayersContainer class serves as a dynamic array, housing two distinct types of layer objects:
* regular layers and overlays. While both types are fundamentally Layer instances and share the same base
* functionality, they differ in their intended use and the order in which they receive updates and events.
*
* Regular layers are typically used for game mechanics, scene rendering, and other core functionalities.
* They are updated in the order they are pushed onto the container, simulating a stack where the first layer
* pushed is the first one to be updated and to receive events. This order ensures a logical flow of dependencies,
* where game logic is often dependent on the sequence of layer updates.
*
* Overlays, on the other hand, are generally employed for UI elements or in-game menus that should always appear
* on top of regular layers and retain functionality regardless of the underlying layers. They are updated after
* all regular layers have been processed, receiving priority in event handling. This ensures that overlays can
* intercept events before they propagate down to the game layers, which is often desirable in a user interface
* context.
*
* The LayersContainer maintains a single vector but uses an insertion index to delineate the boundary between
* layers and overlays. Regular layers are inserted up to this boundary, maintaining the stack's order, whereas
* overlays are appended beyond this point. Such an arrangement simplifies the management of layers while allowing
* for complex interactions between different layer types within a unified structure.
* 
* @see Layer
* @version 1.0
* @date 2023-10-27
* @author Secareanu Filip
*/

#include "layer.h"

namespace GLOPHYSX {

	/**
	* @class LayersContainer
	* @brief A container that handles the insertion and removal of Layers in a defined order.
	*
	* The LayersContainer is responsible for maintaining a collection of pointers to Layer objects.
	* It allows adding layers (which update and receive events first) and overlays (which update
	* and receive events after the regular layers). Layers are managed in a stack-like fashion for
	* controlled processing order.
	*/
	class LayersContainer
	{
	public:
		GLOP_API LayersContainer() = default;
		GLOP_API ~LayersContainer();

		GLOP_API void PushLayer(Layer* layer);
		GLOP_API void PushOverlay(Layer* overlay);
		GLOP_API void PopLayer(Layer* layer);
		GLOP_API void PopOverlay(Layer* overlay);

		GLOP_API std::vector<Layer*>::iterator begin() { return m_layers.begin(); }
		GLOP_API std::vector<Layer*>::iterator end() { return m_layers.end(); }
		GLOP_API std::vector<Layer*>::reverse_iterator rbegin() { return m_layers.rbegin(); }
		GLOP_API std::vector<Layer*>::reverse_iterator rend() { return m_layers.rend(); }

		GLOP_API std::vector<Layer*>::const_iterator begin() const { return m_layers.begin(); }
		GLOP_API std::vector<Layer*>::const_iterator end()	const { return m_layers.end(); }
		GLOP_API std::vector<Layer*>::const_reverse_iterator rbegin() const { return m_layers.rbegin(); }
		GLOP_API std::vector<Layer*>::const_reverse_iterator rend() const { return m_layers.rend(); }

	private:
		std::vector<Layer*> m_layers;
		unsigned int m_layer_insert_index = 0;
	};
}
