#pragma once
#include "hzpch.h"
#include "Hazel/Core.h"
#include "Events/Event.h"

namespace Hazel {
	//窗口的属性 Title,Width,Height
	struct WindowProps
	{
		std::string Title;
		unsigned int Width,Height;
		WindowProps(const std::string& title="Hazel Engine",
					unsigned int width = 1200,
					unsigned int height = 720)
			:Title(title),Width(width),Height(height){}
	};
	//创建一个窗口接口
	//由Platform下的文件继承实现
	//没有任何数据
	class HAZEL_API Window
	{
	public:
		//函数指针返回void传入Event&
		using EventCallbackFn = std::function<void(Event&)>;
		
		virtual ~Window() {}
		virtual void OnUpdate() = 0;
		virtual unsigned int GetWidth()const = 0;
		virtual unsigned int GetHeight()const = 0;

		//属性
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync()const = 0;

		static Window* Create(const WindowProps& props = WindowProps());
	};
}