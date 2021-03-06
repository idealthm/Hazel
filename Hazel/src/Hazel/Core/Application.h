#pragma once
#include "Hazel/Core/layerStack.h"
#include "Hazel/Core/Base.h"
#include "Hazel/Events/Event.h"
#include "Window.h"

#include "Hazel/Events/ApplicationEvent.h"

#include "Hazel/ImGui/ImGuiLayer.h"
#include "Hazel/Renderer/Shader.h"
#include "Hazel/Renderer/VertexArray.h"
#include "Hazel/Renderer/Buffer.h"

#include <Hazel/Renderer/OrthographicCamera.h>

#include <Hazel/Core/Timestep.h>

namespace Hazel {
	class HAZEL_API Application
	{
	public:
		Application();
		
		virtual ~Application();
		
		void Run();
		void Close();

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
		ImGuiLayer* m_ImGuiLayer;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;
		bool m_MouseEnabled = true;
		static Application* s_Instance;
	};

	// To be defined in client
	//声明一个待实现的函数,外部应用继承实现Application之后,EntryPoint中调用该函数.
	//做到只有一个由引擎控制main入口.
	//控制程序的流程
	Application* CreateApplication();
}