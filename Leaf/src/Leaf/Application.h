#pragma once

#include "Leaf/Core.h"
#include "Leaf/Events/IEvent.h"

namespace Leaf {
	class LEAF_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	//To be defined in client
	Application* CreateLeaf();
}

