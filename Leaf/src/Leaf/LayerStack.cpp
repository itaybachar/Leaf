#include "lfpch.h"
#include "LayerStack.h"

namespace Leaf {

	LayerStack::LayerStack()
	{
	}

	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_LayerStack)
			delete layer;
	}

	void LayerStack::PushLayer(Layer* l)
	{
		 m_LayerStack.emplace(m_LayerStack.begin() + m_CurrentPositionIndex, l);
		 m_CurrentPositionIndex++;
		l->OnAttach();
	}

	void LayerStack::PopLayer(Layer* l)
	{
		auto pos = std::find(m_LayerStack.begin(), m_LayerStack.end(), l);
		if (pos != m_LayerStack.end()) {
			m_LayerStack.erase(pos);
			m_CurrentPositionIndex--;
			l->OnDetach();
		}
	}

	void LayerStack::PushOverlay(Layer* l)
	{
		m_LayerStack.emplace_back(l);
		l->OnAttach();
	}

	void LayerStack::PopOverlay(Layer* l)
	{
		auto pos = std::find(m_LayerStack.begin(), m_LayerStack.end(), l);
		if (pos != m_LayerStack.end()) {
			m_LayerStack.erase(pos);
			l->OnDetach();
		}
	}
}
