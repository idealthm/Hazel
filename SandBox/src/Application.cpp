#include <hzpch.h>
#include "Hazel.h"
class Sandbox :public Hazel::Application
{
public:
	Sandbox() {

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