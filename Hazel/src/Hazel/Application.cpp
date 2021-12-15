#include "hzpch.h"

#include "Application.h"
#include "Events/ApplicationEvent.h"

//#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "Input.h"

#include "Renderer/Buffer.h"
#include "Renderer/Shader.h"

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

		m_VertexArray.reset(VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f , 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.2f, 0.8f , 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f , 1.0f
		};

		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		BufferLayout layout = {
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float4, "a_Color"}
		};

		m_VertexBuffer->SetLayout(layout);

		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		unsigned int indices[3] = { 0, 1, 2 };
		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices)/sizeof(uint32_t)));

		m_VertexArray->SetIndexBuffer(m_IndexBuffer);
		//m_VertexBuffer->Bind();
		//m_IndexBuffer->Bind();


		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = vec4(a_Position,1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position*0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader.reset(new Shader(vertexSrc,fragmentSrc));
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
			glClearColor(0.2f, 0.1f, 0.3f, 1);
			//��֮ǰ��ɫȫ�����.�ָ�Ϊ��Ļ��ɫ
			//GL_COLOR_BUFFER_BIT ָ��Ϊ��ǰ������Ϊд��������ɫ����
			glClear(GL_COLOR_BUFFER_BIT);

			m_Shader->Bind();
			m_VertexArray->Bind();
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

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