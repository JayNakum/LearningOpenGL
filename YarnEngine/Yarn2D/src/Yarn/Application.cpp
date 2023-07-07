#include "YarnPCH.h"

#include "Application.h"

#include "glad/glad.h"


// File containing the definitions for Application Class methods.
namespace Yarn {
	
		Application* Application::s_instance = nullptr;

	Application::Application()
	{
		YARN_CORE_ASSERT(!s_instance, "Application already exists!");
		s_instance = this;

		m_window = std::unique_ptr<Window>(Window::create());
		m_window->setEventCallback(YARN_BIND_EVENT_FUNCTION(Application::onEvent));
	}

	Application::~Application() {}

	void Application::pushLayer(Layer* layer)
	{
		m_layerStack.pushLayer(layer);
		layer->onAttach();
	}

	void Application::pushOverlay(Layer* overlay)
	{
		m_layerStack.pushOverlay(overlay);
		overlay->onAttach();
	}

	void Application::onEvent(Event& e)
	{
		EventDispatcher dispatcher(e);

		dispatcher.dispatch<WindowCloseEvent>(YARN_BIND_EVENT_FUNCTION(Application::onWindowClose));
		
		// YARN_CORE_TRACE("{0}", e);

		for (auto it = m_layerStack.end(); it != m_layerStack.begin(); )
		{
			(*--it)->onEvent(e);;
			if (e.m_isHandled)
				break;
		}
	}

	void Application::run()
	{
		while (m_isRunning)
		{
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : m_layerStack)
				layer->onUpdate();

			m_window->onUpdate();
		}
	}

	bool Application::onWindowClose(WindowCloseEvent& e)
	{
		m_isRunning = false;
		return true;
	}

}