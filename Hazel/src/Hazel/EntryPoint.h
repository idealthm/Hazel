#pragma once

#ifdef HZ_PLATFORM_WINDOWS

//声明一个函数,其定义在Haze/Application,实现在外部应用
//先用于编译,连接后生效
extern Hazel::Application* Hazel::CreateApplication();

int main(int argc, char** argv)
{
	//静态成员函数
	Hazel::Log::Init();
	//创建一个窗口
	auto app = Hazel::CreateApplication();
	app->Run();
	delete app;
}

#endif