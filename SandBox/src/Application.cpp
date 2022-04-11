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
	//该应用的void run();函数才是真正的运行.
	//定义在Application.cpp
};
//实现一个函数用于EnrtyPoint调用
//函数声明在Hazel/Application.h
Hazel::Application* Hazel::CreateApplication()
{
	return new Sandbox();
}
