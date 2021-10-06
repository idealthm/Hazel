#include "hzpch.h"

#include "Application.h"
#include "Events/ApplicationEvent.h"

#include <GLFW/glfw3.h>
namespace Hazel {

#define BIND_EVENT_FN(x) std::bind(&x,this,std::placeholders::_1)
		//Application 被创建时会创建一个Window
		//m_Running 用于控制该窗口是否继续运行.
		//Window::Create() 是静态函数.
		// 由Window(接口) 定义
		// WindowsWindow 继承Window后,实现WindowsWindow
		// 而Window::Create()中返回的是一个WindowsWindow实例
		// 类似于引擎App和应用App
		//调用后生成该类的一个实例
		Application::Application() {
			m_Window = std::unique_ptr<Window>(Window::Create());	

			//为窗口的函数指针绑定回调函数.
			m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
		}
		Application::~Application() {

		}

		void Application::OnEvent(Event& e)
		{
			EventDispatcher dispatcher(e);
			//初步完成检测到不同事件时的动作.
			dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

			HZ_CORE_TRACE("{0}", e);
		}

		void Application::Run()
		{
			while (m_Runing)
			{
				//红、绿、蓝和 alpha 值，指定值范围均为[ 0.0f,1.0f ]
				//指定屏幕底色.
				glClearColor(1, 0, 1, 1);
				//将之前颜色全部清除.恢复为屏幕底色
				//GL_COLOR_BUFFER_BIT 指定为当前被激活为写操作的颜色缓存
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