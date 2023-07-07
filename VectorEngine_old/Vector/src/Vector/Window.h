#pragma once

#include "VectorPCH.h"
#include "Core.h"

namespace Vector {
	struct WindowProperties
	{
		std::string title;
		unsigned int width;
		unsigned int height;

		WindowProperties(const std::string& title = "Vector Engine",
			unsigned int width = 1280,
			unsigned int height = 720)
		{
			this->title = title;
			this->width = width;
			this->height = height;
		}
	};

	class VECTOR_API Window
	{
	public:
		static Window* create(const WindowProperties& properties = WindowProperties());

	public:
		virtual ~Window() {}

		virtual void onUpdate() = 0;

		virtual unsigned int getWidth() const = 0;
		virtual unsigned int getHeight() const = 0;

		virtual void setVSync(bool enabled) = 0;
		virtual bool isVSync() const = 0;

		virtual inline bool windowShouldClose() const = 0;
	};

}