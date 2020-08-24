#include "lfpch.h"

#include "Leaf/Application.h"
#include "Leaf/Logger.h"
#include "Leaf/KeyCodes.h"
#include "Leaf/Inputs.h"

#include "Leaf/Renderer/Renderer.h"

namespace Leaf {
	Application* Application::s_Instance = nullptr;

	
	Application::Application()
		: m_Camera(OrthographicCamera(-1.78f, 1.78f, -1.0f, 1.0f))
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
		handler.DispatchEvent<WindowResizeEvent>(BIND_EVENT_FN(Application::OnWindowResize));
		handler.DispatchEvent<KeyPressEvent>(BIND_EVENT_FN(Application::OnKeyPress));

	}

	void Application::Run()
	{
		//Render Loop
		while (m_IsRunning) {

			//Clear Buffers
			RenderCommand::SetClearColor({ 0.15f, 0.15f, 0.15f, 1 });
			RenderCommand::Clear();


			m_Camera.SetRotate(m_Rot, { 0.0f,0.0f,1.0f });
			m_Camera.SetTranslation({ m_Tx,m_Ty,0.0f });

			Renderer::BeginScene(m_Camera);
			{
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
			Renderer::EndScene();
		}
	}
	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_IsRunning = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		return true;
	}

	bool Application::OnKeyPress(KeyPressEvent& e)
	{
		switch (e.GetKeycode())
		{
			case LF_KEY_W:
				m_Ty += 0.05f;
				break;
			case LF_KEY_S:
				m_Ty -= 0.05f;
				break;
			case LF_KEY_A:
				m_Tx -= 0.05f;
				break;
			case LF_KEY_D:
				m_Tx += 0.05f;
				break;
			case LF_KEY_RIGHT:
				m_Rot += 1.0f;
				break;
			case LF_KEY_LEFT:
				m_Rot -= 1.0f;
				break;
		}

		return true;
	}
}

