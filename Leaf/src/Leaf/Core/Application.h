#pragma once
#include "Leaf/Core/Core.h"
#include "Leaf/Core/Window.h"
#include "Leaf/Core/LayerStack.h"

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

		bool OnWindowResize(WindowResizeEvent& e);

	private:
		Scope<Window> m_Leaf;

		ImGuiLayer* m_ImGuiLayer;
		LayerStack m_Layers;

		bool m_IsRunning;
		bool m_Minimized = false;
		float m_LastTime = 0.0f;
	private:
		static Application* s_Instance;
	};

	//To be defined in client
	Application* CreateLeaf();
}

