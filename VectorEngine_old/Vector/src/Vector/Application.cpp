#include "VectorPCH.h"

#include "Application.h"

#include "glad/glad.h"

namespace Vector {

	Application* Application::s_instance = nullptr;
	
	void Application::run()
	{
		while (!m_window->windowShouldClose())
		{
			glClear(GL_COLOR_BUFFER_BIT);

			m_window->onUpdate();
		}
	}

	

	Application::Application()
	{
		if (!s_instance)
			s_instance = this;

		m_window = std::unique_ptr<Window>(Window::create());
	}

	Application::~Application()
	{
	}
}