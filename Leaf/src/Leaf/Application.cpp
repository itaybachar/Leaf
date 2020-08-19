#include "lfpch.h"

#include "Leaf/Application.h"
#include "Leaf/Logger.h"

#include <glad/glad.h>

namespace Leaf {
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		LF_ASSERT(!s_Instance, "Application is already created!");
		s_Instance = this;

		m_Leaf = std::unique_ptr<Window>(Window::Create());
		m_Leaf->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
		m_IsRunning = true;

		//Create ImGui Layer
		m_ImGuiLayer = new ImGuiLayer();
		m_Layers.PushOverlay(m_ImGuiLayer);
	}

	Application::~Application()
	{
	}

	void Application::OnEvent(IEvent& e)
	{
		for (auto it = m_Layers.end(); it != m_Layers.begin();) {
			(*--it)->OnEvent(e);
			if (e.m_IsHandled)
				break;
		}

		//Window Close
		EventDispatcher handler(e);
		handler.DispatchEvent<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
	}

	void Application::Run()
	{
		//Render Loop
		while (m_IsRunning) {

			//Clear Buffers
			glClearColor(0.9f, 0.9f, 0.9f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			//Render normal opengl first
			for (Layer* l : m_Layers) {
				l->OnUpdate();
			}

			//Render ImGui
			m_ImGuiLayer->Begin();
			for (Layer* l : m_Layers) {
				l->OnImGuiUpdate();
			}
			m_ImGuiLayer->End();

			m_Leaf->OnUpdate();
		}
	}
	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_IsRunning = false;
		return true;
	}
}

