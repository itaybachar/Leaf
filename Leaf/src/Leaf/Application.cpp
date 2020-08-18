#include "lfpch.h"

#include "Leaf/Application.h"
#include "Leaf/Logger.h"

namespace Leaf {
	Application::Application()
	{
		m_Leaf = std::unique_ptr<Window>(Window::Create());
		m_Leaf->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
		m_IsRunning = true;
	}

	Application::~Application()
	{
	}

	void Application::OnEvent(IEvent& e)
	{
		LF_CORE_TRACE(e);

		EventDispatcher handler(e);

		handler.DispatchEvent<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
	}

	void Application::Run()
	{
		while (m_IsRunning) {
			m_Leaf->OnUpdate();
		}
	}
	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_IsRunning = false;
		return true;
	}
}

