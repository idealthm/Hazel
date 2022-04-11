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
	HZ_PROFILE_BEGIN_SESSION("Startup", "HazelProfile-startup.json");
	auto app = Hazel::CreateApplication();
	HZ_PROFILE_END_SESSION();

	HZ_PROFILE_BEGIN_SESSION("Runtime", "HazelProfile-runtime.json");
	app->Run();
	HZ_PROFILE_END_SESSION();

	HZ_PROFILE_BEGIN_SESSION("Shutdown", "HazelProfile-shutdown.json");
	delete app;
	HZ_PROFILE_END_SESSION();
}
#endif