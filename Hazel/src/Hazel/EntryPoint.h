#pragma once

#ifdef HZ_PLATFORM_WINDOWS

//����һ������,�䶨����Haze/Application,ʵ�����ⲿӦ��
//�����ڱ���,���Ӻ���Ч
extern Hazel::Application* Hazel::CreateApplication();

int main(int argc, char** argv)
{
	//��̬��Ա����
	Hazel::Log::Init();
	//����һ������
	auto app = Hazel::CreateApplication();
	app->Run();
	delete app;
}

#endif