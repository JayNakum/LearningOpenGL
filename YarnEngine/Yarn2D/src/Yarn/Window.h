#pragma once

#include "YarnPCH.h"

#include "Yarn/Core.h"
#include "Yarn/Events/Event.h"

namespace Yarn {

	struct WindowProperties
	{
		std::string title;
		unsigned int width;
		unsigned int height;

		WindowProperties(const std::string& title = "Yarn Engine",
					unsigned int width = 1280,
					unsigned int height = 720 )
		{
			this->title = title;
			this->width = width;
			this->height = height;
		}
	};

	// Window is an interface representing a desktop window
	// It will be implement by platform specific window class
	class YARN_API Window
	{
	public:
		using EventCallbackFunction = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void onUpdate() = 0;

		virtual unsigned int getWidth() const = 0;
		virtual unsigned int getHeight() const = 0;

		// Window Attributes
		virtual void setEventCallback(const EventCallbackFunction& callback) = 0;
		virtual void setVSync(bool enabled) = 0;
		virtual bool isVSync() const = 0;

		static Window* create(const WindowProperties& properties = WindowProperties());
	};

}