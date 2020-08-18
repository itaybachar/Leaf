#include "lfpch.h"

#include "Leaf/Application.h"
#include "Leaf/Events/KeyEvent.h"
#include "Leaf/Events/ApplicationEvent.h"
#include "Leaf/Logger.h"

namespace Leaf {
	Application::Application()
	{
		m_Leaf = std::unique_ptr<Window>(Window::Create());
		m_IsRunning = true;
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (m_IsRunning) {
			m_Leaf->OnUpdate();
		}
	}
}

