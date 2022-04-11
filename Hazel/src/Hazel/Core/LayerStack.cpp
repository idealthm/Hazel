#include "hzpch.h"
#include "LayerStack.h"

namespace Hazel {

	LayerStack::LayerStack()
	{
		
	}

	LayerStack::~LayerStack()
	{
		HZ_PROFILE_FUNCTION();

		for (auto it : m_Layers)
			delete it;
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		HZ_PROFILE_FUNCTION();

		m_Layers.emplace(m_Layers.begin()+ m_LayerInsertIndex, layer);
		m_LayerInsertIndex++;
	}

	void LayerStack::PushOverlay(Layer* overlayer)
	{
		HZ_PROFILE_FUNCTION();

		m_Layers.emplace_back(overlayer);
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		HZ_PROFILE_FUNCTION();

		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
			m_LayerInsertIndex--;
		}
	}

	void LayerStack::PopOverlay(Layer* overlayer)
	{
		HZ_PROFILE_FUNCTION();

		auto it = std::find(m_Layers.begin(), m_Layers.end(), overlayer);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
		}
	}
}