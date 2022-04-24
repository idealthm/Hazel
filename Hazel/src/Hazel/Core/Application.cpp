#include "hzpch.h"

#include "Application.h"
#include "Hazel/Events/ApplicationEvent.h"

//#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Input.h"

#include "Hazel/Renderer/Buffer.h"
#include "Hazel/Renderer/Shader.h"

#include <Hazel/Renderer/Renderer.h>


namespace Hazel {

#define BIND_EVENT_FN(x) std::bind(&x,this,std::placeholders::_1)

	Application* Application::Application::s_Instance = nullptr;


	//Application ������ʱ�ᴴ��һ��Window
	//m_Running ���ڿ��Ƹô����Ƿ��������.
	//Window::Create() �Ǿ�̬����.
	// ��Window(�ӿ�) ����
	// WindowsWindow �̳�Window��,ʵ��WindowsWindow
	// ��Window::Create()�з��ص���һ��WindowsWindowʵ��
	// ����������App��Ӧ��App
	//���ú����ɸ����һ��ʵ�� 
	Application::Application() 
	{
		HZ_PROFILE_FUNCTION();


		HZ_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());	

		// Ϊ���ڵĺ���ָ��󶨻ص�����.
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);


	}
	Application::~Application() {

	}

	void Application::PushLayer(Layer* layer)
	{
		HZ_PROFILE_FUNCTION();

		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		HZ_PROFILE_FUNCTION();

		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		HZ_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		//������ɼ�⵽��ͬ�¼�ʱ�Ķ���.
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
		HZ_PROFILE_FUNCTION();

		while (m_Runing)
		{
			float time = (float)glfwGetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;
			//��ȥһЩ�¼�����,����ҪһЩͼ��,���米��...
			if ( !m_Minimized ) {
				HZ_PROFILE_SCOPE("LayerStack OnUpdate");

				for (Layer* layer : m_LayerStack)
					layer->OnUpdate(timestep);
			}
			
			//
			
			HZ_PROFILE_SCOPE("ImGuiLayerStack OnUpdate");
			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();	
			

			m_Window->OnUpdate();
		}
	}
		
	void Application::Close ()
	{
		m_Runing = false;
	}

	bool Application::OnWindowCloseEvent(WindowCloseEvent& e) 
	{
		HZ_PROFILE_FUNCTION();

		m_Runing = false;
		return true;
	}

	bool Application::OnWindowResizeEvent(WindowResizeEvent& e) 
	{
		HZ_PROFILE_FUNCTION();

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
		HZ_PROFILE_FUNCTION();
		m_MouseEnabled ^= true;
		if (Input::IsKeyPressed(GLFW_KEY_ESCAPE)) 
		{
			Renderer::SetCursorDisabled(m_MouseEnabled);
			return true;
		}
		return false;
	}
}