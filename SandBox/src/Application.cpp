#include "Hazel.h"

class ExampleLayer : public Hazel::Layer
{
public:
	ExampleLayer()
		:Layer("Example")
	{}
	
	void OnUpdate() override
	{
		if (Hazel::Input::IsKeyPressed(HZ_KEY_TAB))
			HZ_INFO("TAB key is pressed");
	}

	void OnEvent(Hazel::Event& e) override
	{
		//HZ_INFO("{0}",e);
	}

private:

};


class Sandbox :public Hazel::Application
{
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
		PushOverlay(new Hazel::ImGuiLayer());
	}
	~Sandbox() {

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