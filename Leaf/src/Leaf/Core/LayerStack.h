#pragma once
#include "Leaf/Core/Layer.h"

#include <vector>

namespace Leaf {

	class LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* l);
		void PopLayer(Layer* l);

		void PushOverlay(Layer* l);
		void PopOverlay(Layer* l);

		//Allows foreach
		inline std::vector<Layer*>::iterator const begin() { return m_LayerStack.begin(); }
		inline std::vector<Layer*>::iterator const end() { return m_LayerStack.end(); }

	private:
		std::vector<Layer*> m_LayerStack;
		uint32_t m_CurrentPositionIndex = 0;
	};
}