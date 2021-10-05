#include "hzpch.h"
#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "Hazel/Log.h"

namespace Hazel {

		Application::Application() {

		}
		Application::~Application() {

		}

		void Application::run()
		{
			WindowsResizeEvent e(1200, 720);
			HZ_TRACE(e);
			while (true);
		}
}