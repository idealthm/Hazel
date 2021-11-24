#include "hzpch.h"

#include "Application.h"
#include "Events/ApplicationEvent.h"

//#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "Input.h"
namespace Hazel {

#define BIND_EVENT_FN(x) std::bind(&x,this,std::placeholders::_1)

	Application* Application::Application::s_Instance = nullptr;

		//Application 被创建时会创建一个Window
		//m_Running 用于控制该窗口是否继续运行.
		//Window::Create() 是静态函数.
		// 由Window(接口) 定义
		// WindowsWindow 继承Window后,实现WindowsWindow
		// 而Window::Create()中返回的是一个WindowsWindow实例
		// 类似于引擎App和应用App
		//调用后生成该类的一个实例 
		Application::Application() {
			HZ_CORE_ASSERT(!s_Instance, "Application already exists!");
			s_Instance = this;

			m_Window = std::unique_ptr<Window>(Window::Create());	

			//为窗口的函数指针绑定回调函数.
			m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

			m_ImGuiLayer = new ImGuiLayer();
			PushOverlay(m_ImGuiLayer);
		}
		Application::~Application() {

		}

		void Application::PushLayer(Layer* layer)
		{
			m_LayerStack.PushLayer(layer);
			layer->OnAttach();
		}

		void Application::PushOverlay(Layer* layer)
		{
			m_LayerStack.PushOverlay(layer);
			layer->OnAttach();
		}

		void Application::OnEvent(Event& e)
		{
			EventDispatcher dispatcher(e);
			//初步完成检测到不同事件时的动作.
			dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

			HZ_CORE_TRACE("{0}", e);
			
			for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
			{
				(*--it)->OnEvent(e);
				if (e.m_Handled)
					break;
			}
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
				//除去一些事件以外,还需要一些图层,例如背景...
				for (Layer* layer : m_LayerStack)
					layer->OnUpdate();
				//
				m_ImGuiLayer->Begin();
				for (Layer* layer : m_LayerStack)
					layer->OnImGuiRender();
				m_ImGuiLayer->End();

				m_Window->OnUpdate();
			}
		}
		
		bool Application::OnWindowClose(WindowCloseEvent& e) {
			m_Runing = false;
			return true;
		}
}