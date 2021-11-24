#include "hzpch.h"

#include "Application.h"
#include "Events/ApplicationEvent.h"

//#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "Input.h"
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
		Application::Application() {
			HZ_CORE_ASSERT(!s_Instance, "Application already exists!");
			s_Instance = this;

			m_Window = std::unique_ptr<Window>(Window::Create());	

			//Ϊ���ڵĺ���ָ��󶨻ص�����.
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
			//������ɼ�⵽��ͬ�¼�ʱ�Ķ���.
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
				//�졢�̡����� alpha ֵ��ָ��ֵ��Χ��Ϊ[ 0.0f,1.0f ]
				//ָ����Ļ��ɫ.
				glClearColor(1, 0, 1, 1);
				//��֮ǰ��ɫȫ�����.�ָ�Ϊ��Ļ��ɫ
				//GL_COLOR_BUFFER_BIT ָ��Ϊ��ǰ������Ϊд��������ɫ����
				glClear(GL_COLOR_BUFFER_BIT);
				//��ȥһЩ�¼�����,����ҪһЩͼ��,���米��...
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