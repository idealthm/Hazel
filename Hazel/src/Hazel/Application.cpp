#include "hzpch.h"

#include "Application.h"
#include "Events/ApplicationEvent.h"

//#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Input.h"

#include "Renderer/Buffer.h"
#include "Renderer/Shader.h"

#include <Hazel/Renderer/Renderer.h>


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
	Application::Application() 
	{
		HZ_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());	

		// 为窗口的函数指针绑定回调函数.
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		Renderer::Init();

		//m_ImGuiLayer = new ImGuiLayer();
		//PushOverlay(m_ImGuiLayer);


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
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowCloseEvent));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(Application::OnWindowResizeEvent));
		dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(Application::OnKeyPressedEvent));
		//HZ_CORE_TRACE("{0}", e);
			
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
			float time = (float)glfwGetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;
			//除去一些事件以外,还需要一些图层,例如背景...
			if ( !m_Minimized ) {
				for (Layer* layer : m_LayerStack)
					layer->OnUpdate(timestep);
			}
			
			//
			/*m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();*/

			m_Window->OnUpdate();
		}
	}
		
	bool Application::OnWindowCloseEvent(WindowCloseEvent& e) {
		m_Runing = false;
		return true;
	}

	bool Application::OnWindowResizeEvent(WindowResizeEvent& e) {
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}
		m_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
		return true;
	}

	bool Application::OnKeyPressedEvent(KeyPressedEvent& e)
	{
		if (Input::IsKeyPressed(GLFW_KEY_ESCAPE)) 
		{
			m_Runing = false;
			return true;
		}
		return false;
	}
}