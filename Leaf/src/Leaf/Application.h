#pragma once

#include "Leaf/Core.h"
#include "Leaf/Events/IEvent.h"
#include "Leaf/Window.h"

#include "Leaf/Events/ApplicationEvent.h"
#include "Leaf/LayerStack.h"

namespace Leaf {
	class LEAF_API Application
	{
	public:
		Application();
		virtual ~Application();

		inline void PushLayer(Layer* l) { m_Layers.PushLayer(l); }
		inline void PushOverlay(Layer* l) { m_Layers.PushOverlay(l); }

		void OnEvent(IEvent& e);

		void Run();
	private:
		bool OnWindowClose(WindowCloseEvent& e);

	private:
		std::unique_ptr<Window> m_Leaf;
		LayerStack m_Layers;

		bool m_IsRunning;
	};

	//To be defined in client
	Application* CreateLeaf();
}

