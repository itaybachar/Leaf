#include "Leaf/Application.h"
#include "Leaf/Events/KeyEvent.h"
#include "Leaf/Events/ApplicationEvent.h"
#include "Leaf/Logger.h"

namespace Leaf {
	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		Leaf::KeyPressEvent e(2, 1);
		Leaf::WindowResizeEvent e2(840, 1230);

		if (e.IsInCategory(Leaf::EventCategory::KeyboardEvent))
			LF_CORE_TRACE("Event found! {0}", e);
		LF_CORE_INFO("{0}", e2);

		while (true);
	}
}

