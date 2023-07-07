#pragma once

#include "Event.h"

namespace Yarn {

	class YARN_API MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y)
			: m_mouseX(x), m_mouseY(y) {}
		
		inline float getX() const { return m_mouseX; }
		inline float getY() const { return m_mouseY; }
	
		std::string toString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_mouseX << ", " << m_mouseY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	
	private:
		float m_mouseX, m_mouseY;
	};

	class YARN_API MouseButtonEvent : public Event
	{
		// Every MouseButtonEvent has a common mouseButton
		// hence we have a base class for all the mouse button events containing a button
	public:
		inline int getMouseButton() const { return m_button; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	protected:
		MouseButtonEvent(int button)
			: m_button(button) {}

		int m_button;
	};

	class YARN_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button)
			: MouseButtonEvent(button) {}

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class YARN_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button)
			: MouseButtonEvent(button) {}

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};

	class YARN_API MouseScrollEvent : public Event
	{
	public:
		MouseScrollEvent(float offsetX, float offsetY)
			: m_offsetX(offsetX), m_offsetY(offsetY) {}

		inline float getOffsetX() const { return m_offsetX; }
		inline float getOffsetY() const { return m_offsetY; }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "MouseScrollEvent: " << m_offsetX << ", " << m_offsetY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
		
	private:
		float m_offsetX, m_offsetY;
	};

}