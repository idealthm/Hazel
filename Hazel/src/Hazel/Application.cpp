#include "hzpch.h"

#include "Application.h"
#include "Events/ApplicationEvent.h"

#include <GLFW/glfw3.h>
namespace Hazel {

#define BIND_EVENT_FN(x) std::bind(&x,this,std::placeholders::_1)
		//Application ������ʱ�ᴴ��һ��Window
		//m_Running ���ڿ��Ƹô����Ƿ��������.
		//Window::Create() �Ǿ�̬����.
		// ��Window(�ӿ�) ����
		// WindowsWindow �̳�Window��,ʵ��WindowsWindow
		// ��Window::Create()�з��ص���һ��WindowsWindowʵ��
		// ����������App��Ӧ��App
		//���ú����ɸ����һ��ʵ��
		Application::Application() {
			m_Window = std::unique_ptr<Window>(Window::Create());	

			//Ϊ���ڵĺ���ָ��󶨻ص�����.
			m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
		}
		Application::~Application() {

		}

		void Application::OnEvent(Event& e)
		{
			EventDispatcher dispatcher(e);
			//������ɼ�⵽��ͬ�¼�ʱ�Ķ���.
			dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

			HZ_CORE_TRACE("{0}", e);
		}

		void Application::Run()
		{
			while (m_Runing)
			{
				//�졢�̡����� alpha ֵ��ָ��ֵ��Χ��Ϊ[ 0.0f,1.0f ]
				//ָ����Ļ��ɫ.
				glClearColor(1, 0, 1, 1);
				//��֮ǰ��ɫȫ�����.�ָ�Ϊ��Ļ��ɫ
				//GL_COLOR_BUFFER_BIT ָ��Ϊ��ǰ������Ϊд��������ɫ����
				glClear(GL_COLOR_BUFFER_BIT);
				//
				m_Window->OnUpdate();
			}
		}
		
		bool Application::OnWindowClose(WindowCloseEvent& e) {
			m_Runing = false;
			return true;
		}
}