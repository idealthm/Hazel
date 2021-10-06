#pragma once
#include "Hazel/layerStack.h"
#include "Core.h"
#include "Events/Event.h"
#include "Window.h"

#include "Events/ApplicationEvent.h"

namespace Hazel {
	class HAZEL_API Application
	{
	public:
		Application();
		
		virtual ~Application();
		
		void Run();

		//void PushLayer(Layer* layer);
		//void PushOverlay(Layer* overlay);
		void  OnEvent(Event& e);
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		std::unique_ptr<Window> m_Window;
		bool m_Runing = true;
		//LayerStack m_LayerStack;
	};

	// To be defined in client
	//����һ����ʵ�ֵĺ���,�ⲿӦ�ü̳�ʵ��Application֮��,EntryPoint�е��øú���.
	//����ֻ��һ�����������main���.
	//���Ƴ��������
	Application* CreateApplication();
}