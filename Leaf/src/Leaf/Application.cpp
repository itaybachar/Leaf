#include "lfpch.h"

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
		Leaf::WindowResizeEvent e2(840, 1230);
		LF_CORE_INFO("{0}", e2);

		while (true);
	}
}

