#include "Hazel.h"

#include "ImGui/imgui.h"

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

	void OnImGuiRender()
	{
		/*ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();*/
	}

private:

};


class Sandbox :public Hazel::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}
	~Sandbox() {

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