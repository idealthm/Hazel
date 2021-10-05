#pragma once

#include "Event.h"


namespace Hazel {
	class HAZEL_API WindowsResizeEvent : public Event
	{
	public:
		WindowsResizeEvent(unsigned int Width,unsigned int height)
			: m_Width(Width),m_Height(height){}

		inline unsigned int GetWidth()const { return m_Width; }
		inline unsigned int GetHeight()const { return m_Height; }

		std::string ToString()const override {
			std::stringstream ss;
			ss << "WindowsResizeEvent: " << m_Width << "," << m_Height;
			return ss.str();
		}
		//加入宏定义函数.
		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)

	private:
		unsigned int m_Width, m_Height;
	};

	class HAZEL_API WindowsCloseEvent : public Event
	{
	public:
		WindowsCloseEvent(){}

		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class HAZEL_API AppTickEvent : public Event
	{
	public:
		AppTickEvent() {}

		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class HAZEL_API AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() {}

		EVENT_CLASS_TYPE(AppUpdate)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class HAZEL_API AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() {}

		EVENT_CLASS_TYPE(AppRender)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
}