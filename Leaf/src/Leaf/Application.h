#pragma once

#include "Leaf/Core.h"
#include "Leaf/Events/IEvent.h"
#include "Leaf/Window.h"

namespace Leaf {
	class LEAF_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

	private:
		std::unique_ptr<Window> m_Leaf;
		bool m_IsRunning;
	};

	//To be defined in client
	Application* CreateLeaf();
}

