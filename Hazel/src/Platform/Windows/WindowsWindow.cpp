#include "hzpch.h"
#include "WindowsWindow.h"

#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Events/KeyEvent.h"
#include "Hazel/Events/MouseEvent.h"

#include "glad/glad.h"
//#include "GLFW/glfw3.h"

namespace Hazel {
	static bool s_GLFWInitialized = false;
	static void GLFWErrorCallback(int error, const char* des)
	{
		HZ_CORE_ERROR("GLFW Error((0)): {1}", error, des);
	}

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}
	//该构造函数将会调用Init(),以此将成员GLFWwindow* m_Window初始化
	//并初始化glfwInit()
	//生成真正的窗口
	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		ShutDown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		
		HZ_CORE_INFO("Create windows {0},({1},{2})", props.Title, props.Width, props.Height);
		if (!s_GLFWInitialized)
		{
			int success = glfwInit();
			HZ_CORE_ASSERT(success, "Could not initalize GLFW!");

			glfwSetErrorCallback(GLFWErrorCallback);

			s_GLFWInitialized = true;
		}
		//glfwCreateWindow创建了一个窗口，它可以指定窗口的类型以及尺寸。
		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		//
		glfwMakeContextCurrent(m_Window);

		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		HZ_CORE_ASSERT(status, "Failed to initialize Glad");
		glfwSetWindowUserPointer(m_Window, &m_Data);

		SetVSync(true);

		/*
		* 所有动作由GLFW监控,当发生某事件时,GLFW通过调用HAZEL指定的函数来完成动作,
		* 用户则是为GLFW提供函数实现,以及选择需要的窗口数量,
		* 当前的函数实现为:当发生某种事件时,创建一个事件实体,将其传递给m_Window已经设置好的函数指针(回调函数)
		* 回调函数using EventCallbackFn = std::function<void(Event&)> 接收一个Event实体
		* 当前使用回调函数仅仅是使用日志发送一个事件日志.
		* 分配器函数尚未完成.
		*/

		//Set GLFW callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			WindowData& data = *(WindowData *)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;
			WindowResizeEvent event(width, height);	
			data.EventCallback(event);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent e;
			data.EventCallback(e);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			switch (action) {
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window,unsigned int keycode)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			KeyTypedEvent event(keycode);
			data.EventCallback(event);
		});
		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent e((float)xOffset,(float)yOffset);
			data.EventCallback(e);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseMovedEvent e((float)xPos, (float)yPos);
			data.EventCallback(e);
		});
	}

	void WindowsWindow::ShutDown()
	{
		//glfwDestroyWindow销毁了一个窗口
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate()
	{
		//执行一些事件
		glfwPollEvents();
		/*
			双缓冲
			应用程序使用单缓冲绘图时可能会存在图像闪烁的问题。 
			这是因为生成的图像不是一下子被绘制出来的，而是按照从左到右，由上而下逐像素地绘制而成的。
			最终图像不是在瞬间显示给用户，而是通过一步一步生成的，这会导致渲染的结果很不真实。
			为了规避这些问题，我们应用双缓冲渲染窗口应用程序。
			前缓冲保存着最终输出的图像，它会在屏幕上显示；而所有的的渲染指令都会在后缓冲上绘制。
			当所有的渲染指令执行完毕后，我们交换(Swap)前缓冲和后缓冲，这样图像就立即呈显出来，之前提到的不真实感就消除了。
		*/
		glfwSwapBuffers(m_Window);
	}
	
	void WindowsWindow::SetVSync(bool enabled)
	{
		glfwSwapInterval(enabled?1:0);
		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync()const {
		return m_Data.VSync;
	}
}