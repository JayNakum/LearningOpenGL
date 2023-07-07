#pragma once

#include "Vector/Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Vector {

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProperties& properties);
		~WindowsWindow();

	public:
		inline bool windowShouldClose() const override { return glfwWindowShouldClose(m_window); }
		void onUpdate() override;
		unsigned int getWidth() const override;
		unsigned int getHeight() const override;
		void setVSync(bool enabled) override;
		bool isVSync() const override;

	private:
		GLFWwindow* m_window;
		struct WindowData
		{
			std::string title;
			unsigned int width, height;
			bool vSync;
		}m_data;
	};

}

