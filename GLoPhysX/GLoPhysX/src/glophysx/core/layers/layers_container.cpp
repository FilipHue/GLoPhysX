#include "gxpch.h"
#include "layers_container.h"

namespace GLOPHYSX {

	LayersContainer::~LayersContainer()
	{
		for (Shared<Layer>& layer : m_layers) {
			layer->OnDetach();
		}
	}

	void LayersContainer::PushLayer(Shared<Layer> layer)
	{
		m_layers.emplace(m_layers.begin() + m_layer_insert_index, layer);
		m_layer_insert_index++;
	}

	void LayersContainer::PushOverlay(Shared<Layer> overlay)
	{
		m_layers.emplace_back(overlay);
	}

	void LayersContainer::PopLayer(Shared<Layer> layer)
	{
		auto it = std::find(m_layers.begin(), m_layers.begin() + m_layer_insert_index, layer);
		if (it != m_layers.begin() + m_layer_insert_index) {
			layer->OnDetach();
			m_layers.erase(it);
			m_layer_insert_index--;
		}
	}

	void LayersContainer::PopOverlay(Shared<Layer> overlay)
	{
		auto it = std::find(m_layers.begin() + m_layer_insert_index, m_layers.end(), overlay);
		if (it != m_layers.end()) {
			overlay->OnDetach();
			m_layers.erase(it);
		}
	}
}
