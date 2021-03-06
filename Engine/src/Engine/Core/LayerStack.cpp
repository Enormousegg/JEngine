#include "egpch.h"
#include "LayerStack.h"

namespace Engine {

	LayerStack::LayerStack()
		:m_LayerInsertIndex(0)
	{
	}

	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Layers)
			delete layer;
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		m_Layers.emplace(m_Layers.begin()+m_LayerInsertIndex, layer);
		++m_LayerInsertIndex;
	}

	void LayerStack::PushOverlay(Layer* overlay)
	{
		m_Layers.emplace_back(overlay);
	}

	//此处只是将layer对象从layerstack中移出，但其仍然存在
	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end())
		{
			layer->OnDetach();
			m_Layers.erase(it);
			--m_LayerInsertIndex;
		}
	}

	void LayerStack::PopOverlay(Layer* overlayer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), overlayer);
		if (it != m_Layers.end()) {
			overlayer->OnDetach();
			m_Layers.erase(it);
		}
	}

}