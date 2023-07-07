#pragma once

#include "Core.h"

#include "Window.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"

#include "Yarn/LayerStack.h"

// This is the main Application class of Yarn
// the class contains the main run loop

namespace Yarn {
	class YARN_API Application
	{
	public:
		Application();
		virtual ~Application();

		void run();
		void onEvent(Event& e);

		void pushLayer(Layer* layer);
		void pushOverlay(Layer* overlay);

		inline Window& getWindow() { return *m_window; }

		inline static Application& get() { return *s_instance; }

	private:
		bool onWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_window;
		bool m_isRunning = true;
		LayerStack m_layerStack;

	private:
		static Application* s_instance;
	};

	// To be defined in CLIENT
	Application* createApplication();
}