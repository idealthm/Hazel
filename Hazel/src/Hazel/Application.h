#pragma once
#include "Hazel/layerStack.h"
#include "Core.h"
#include "Events/Event.h"
#include "Window.h"

#include "Events/ApplicationEvent.h"

#include "Hazel/ImGui/ImGuiLayer.h"
#include "Renderer/Shader.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Buffer.h"

#include <Hazel/Renderer/OrthographicCamera.h>

#include <Hazel/Core/Timestep.h>

namespace Hazel {
	class HAZEL_API Application
	{
	public:
		Application();
		
		virtual ~Application();
		
		void Run();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		virtual void  OnEvent(Event& e);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool m_Runing = true;
		bool m_Minimized = false;
		bool OnWindowCloseEvent(WindowCloseEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
	private:
		std::unique_ptr<Window> m_Window;
		//ImGuiLayer* m_ImGuiLayer;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;

		static Application* s_Instance;
	};

	// To be defined in client
	//����һ����ʵ�ֵĺ���,�ⲿӦ�ü̳�ʵ��Application֮��,EntryPoint�е��øú���.
	//����ֻ��һ�����������main���.
	//���Ƴ��������
	Application* CreateApplication();
}