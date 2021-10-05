#pragma once
#include"Core.h"
#include"Events/Event.h"

namespace Hazel {
	class HAZEL_API Application
	{
	public:
		Application();
		virtual ~Application();
		void run();
	};

	// to be defined in client
	Application* CreateApplication();
}