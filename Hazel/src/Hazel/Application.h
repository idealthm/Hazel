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

namespace Hazel {
	class HAZEL_API Application
	{
	public:
		Application();
		
		virtual ~Application();
		
		void Run();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void  OnEvent(Event& e);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Runing = true;
		LayerStack m_LayerStack;

		static Application* s_Instance;

		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;
		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
	};

	// To be defined in client
	//声明一个待实现的函数,外部应用继承实现Application之后,EntryPoint中调用该函数.
	//做到只有一个由引擎控制main入口.
	//控制程序的流程
	Application* CreateApplication();
}