#pragma once

#include "Leaf/Core.h"
#include "Leaf/Events/IEvent.h"
#include "Leaf/Window.h"

#include "Leaf/Events/ApplicationEvent.h"

namespace Leaf {
	class LEAF_API Application
	{
	public:
		Application();
		virtual ~Application();

		void OnEvent(IEvent& e);

		void Run();
	private:
		bool OnWindowClose(WindowCloseEvent& e);

	private:
		std::unique_ptr<Window> m_Leaf;
		bool m_IsRunning;
	};

	//To be defined in client
	Application* CreateLeaf();
}

