#include "YarnPCH.h"

#include "WindowsWindow.h"

#include "Yarn/Events/ApplicationEvent.h"
#include "Yarn/Events/KeyEvent.h"
#include "Yarn/Events/MouseEvent.h"

#include "glad/glad.h"

namespace Yarn {

	static bool s_GLFWInitialized = false;

	static void glfwErrorCallback(int errorCode, const char* description)
	{
		YARN_CORE_ERROR("GLFW Error ({0}): {1}",  errorCode, description);
	}

	Window* Window::create(const WindowProperties& properties)
	{
		return new WindowsWindow(properties);
	}

	WindowsWindow::WindowsWindow(const WindowProperties& properties)
	{
		init(properties);
	}

	WindowsWindow::~WindowsWindow() 
	{
		shutdown();
	}

	void WindowsWindow::init(const WindowProperties& properties)
	{
		m_data.title = properties.title;
		m_data.width = properties.width;
		m_data.height = properties.height;

		YARN_CORE_INFO("Creating window {0} ({1}, {2})", properties.title, properties.width, properties.height);

		if (!s_GLFWInitialized)
		{
			// TODO: glfwTerminate on system shutdown
			int success = glfwInit();

			YARN_CORE_ASSERT(success, "Could not initialize GLFW!");

			glfwSetErrorCallback(glfwErrorCallback);

			s_GLFWInitialized = true;
		}

		m_window = glfwCreateWindow((int)properties.width, (int)properties.height, m_data.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		YARN_CORE_ASSERT(status, "Failed to initialize Glad!");
		glfwSetWindowUserPointer(m_window, &m_data);
		setVSync(true);

		// Set GLFW callback
		glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				data.width = width;
				data.height = height;

				WindowResizeEvent event(width, height);
				data.EventCallback(event);
			});

		glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				WindowCloseEvent event;
				data.EventCallback(event);

			});

		glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) 
			{
				// TODO: Change to custom yarn key codes
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
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
						KeyPressedEvent event(key, 1); // Possible abstraction
						data.EventCallback(event);
						break;
					}
				}
			});

		glfwSetCharCallback(m_window, [](GLFWwindow* window, unsigned int keyCode)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				
				KeyTypedEvent event(keyCode);
				data.EventCallback(event);
			});

		glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods) 
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

		glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xoffset, double yoffset) 
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseScrollEvent event((float)xoffset, (float)yoffset);
				data.EventCallback(event);
			});

		glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xpos, double ypos)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseMovedEvent event((float)xpos, (float)ypos);
				data.EventCallback(event);
			});

	}

	void WindowsWindow::shutdown()
	{
		glfwDestroyWindow(m_window);
	}

	void WindowsWindow::onUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_window);
	}

	void WindowsWindow::setVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_data.vSync = enabled;
	}

	bool WindowsWindow::isVSync() const
	{
		return m_data.vSync;
	}


}