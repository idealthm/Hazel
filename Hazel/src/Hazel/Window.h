#pragma once
#include "hzpch.h"
#include "Hazel/Core.h"
#include "Events/Event.h"

namespace Hazel {
	//���ڵ����� Title,Width,Height
	struct WindowProps
	{
		std::string Title;
		unsigned int Width,Height;
		WindowProps(const std::string& title="Hazel Engine",
					unsigned int width = 1200,
					unsigned int height = 720)
			:Title(title),Width(width),Height(height){}
	};
	//����һ�����ڽӿ�
	//��Platform�µ��ļ��̳�ʵ��
	//û���κ�����
	class HAZEL_API Window
	{
	public:
		//����ָ�뷵��void����Event&
		using EventCallbackFn = std::function<void(Event&)>;
		
		virtual ~Window() {}
		virtual void OnUpdate() = 0;
		virtual unsigned int GetWidth()const = 0;
		virtual unsigned int GetHeight()const = 0;

		//����
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync()const = 0;

		static Window* Create(const WindowProps& props = WindowProps());
	};
}