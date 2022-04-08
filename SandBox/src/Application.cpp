#include "Hazel.h"
#include "Example.h"
#include "Planet.h"
// -----Entry Point-----------------
#include "Hazel/EntryPoint.h"
// ---------------------------------"

class Sandbox :public Hazel::Application
{
public:
	Sandbox()
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new PlanetLayer());
	}
	~Sandbox() {
	}
	
	bool Shutdown() { m_Runing = false; return true; }
	void OnEvent(Hazel::Event& e) override
	{
		//HZ_CORE_TRACE("{0}", e);
		Hazel::EventDispatcher dispatcher(e);
		//初步完成检测到不同事件时的动作.
		dispatcher.Dispatch<Hazel::WindowCloseEvent>(HZ_BIND_EVENT_FN(Sandbox::OnWindowClose));

		dispatcher.Dispatch<Hazel::KeyPressedEvent>(HZ_BIND_EVENT_FN(Sandbox::OnKeyPressedEvent));
		Application::OnEvent(e);

	}

	bool OnKeyPressedEvent(Hazel::KeyPressedEvent& e)
	{
		if (e.GetKeyCode() == HZ_KEY_ESCAPE)
			m_Runing = false;
		return true;
	}

	bool OnWindowClose(Hazel::WindowCloseEvent& e)
	{
		m_Runing = false;
		return true;
	}
	//该应用的void run();函数才是真正的运行.
	//定义在Application.cpp
};
//实现一个函数用于EnrtyPoint调用
//函数声明在Hazel/Application.h
Hazel::Application* Hazel::CreateApplication()
{
	return new Sandbox();
}
