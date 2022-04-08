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
		//������ɼ�⵽��ͬ�¼�ʱ�Ķ���.
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
	//��Ӧ�õ�void run();������������������.
	//������Application.cpp
};
//ʵ��һ����������EnrtyPoint����
//����������Hazel/Application.h
Hazel::Application* Hazel::CreateApplication()
{
	return new Sandbox();
}
