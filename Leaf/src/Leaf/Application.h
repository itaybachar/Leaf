#pragma once

#include "Leaf/Core.h"
#include "Leaf/Window.h"
#include "Leaf/LayerStack.h"

#include "Leaf/Events/IEvent.h"
#include "Leaf/Events/ApplicationEvent.h"

#include "Leaf/ImGui/ImGuiLayer.h"

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

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Leaf; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

	private:
		Scope<Window> m_Leaf;

		ImGuiLayer* m_ImGuiLayer;
		LayerStack m_Layers;

		bool m_IsRunning;
		float m_LastTime = 0.0f;
	private:
		static Application* s_Instance;
	};

	//To be defined in client
	Application* CreateLeaf();
}

