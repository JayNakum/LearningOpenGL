#pragma once

#include "Core.h"

#include "Window.h"

namespace Vector {

	class VECTOR_API Application
	{
	public:
		Application();
		virtual ~Application();

		void run();

	private:
		std::unique_ptr<Window> m_window;
		bool m_isRunning = true;

	private:
		static Application* s_instance;
	};

	Application* createApplication();
}
