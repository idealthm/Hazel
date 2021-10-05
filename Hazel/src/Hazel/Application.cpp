#include "hzpch.h"

#include "Application.h"
#include "Events/ApplicationEvent.h"
//#pragma comment (lib, "opengl32.lib")
#include <GLFW/glfw3.h>
namespace Hazel {

		Application::Application() {
			m_Window = std::unique_ptr<Window>(Window::Create());	
		}
		Application::~Application() {

		}

		void Application::run()
		{
			while (m_Runing)
			{
				glClearColor(1, 0, 1, 1);
				glClear(GL_COLOR_BUFFER_BIT);	
				m_Window->OnUpdate();
			}
		}
}