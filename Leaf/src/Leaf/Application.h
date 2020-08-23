#pragma once

#include "Leaf/Core.h"

#include "Leaf/Window.h"

#include "Leaf/Events/IEvent.h"
#include "Leaf/Events/ApplicationEvent.h"
#include "Leaf/Events/KeyEvent.h"

#include "Leaf/LayerStack.h"
#include "Leaf/ImGui/ImGuiLayer.h"

#include "Leaf/Renderer/Shader.h"
#include "Leaf/Renderer/VertexArray.h"

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
		bool OnKeyPress(KeyPressEvent& e);

	private:
		std::unique_ptr<Window> m_Leaf;

		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VArray;

		std::shared_ptr<Shader> m_SolidShader;
		std::shared_ptr<VertexArray> m_SquareVA;

		ImGuiLayer* m_ImGuiLayer;
		LayerStack m_Layers;

		bool m_IsRunning;
	private:
		static Application* s_Instance;
	};

	//To be defined in client
	Application* CreateLeaf();
}

