#include "Hazel.h"
#include "Example.h"
#include "Planet.h"
// -----Entry Point-----------------
#include "Hazel/Core/EntryPoint.h"
// ---------------------------------"
#include "Sandbox2D.h"
class Sandbox :public Hazel::Application
{
public:
	Sandbox()
	{
		//PushLayer(new ExampleLayer());
		//PushLayer(new PlanetLayer());
		PushLayer(new Sanbox2D());

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
