#pragma once

#include "Event.h"

namespace Yarn {

	// Every KeyEvent has a keyCode common
	// hence we have a base class for all the key events containing a keyCode
	class YARN_API KeyEvent : public Event
	{
	public:
		inline int getKeyCode() const { return m_keyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

	protected:
		// No other class or method is allowed to construct an object for keyEvent
		// Only the child classes can create its object
		KeyEvent(int keyCode)
			: m_keyCode(keyCode) {}

		int m_keyCode;
	};

	// KeyPressedEvent handles when a key is either pressed or long pressed
	// long pressed is handled by repeatCount
	class YARN_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keyCode, int repeatCount)
			: KeyEvent(keyCode), m_repeatCount(repeatCount) {}

		inline int getRepeatCount() const { return m_repeatCount; }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_keyCode
				<< " (" << m_repeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)

	private:
		int m_repeatCount;
	};

	class YARN_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keyCode)
			: KeyEvent(keyCode) {}

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_keyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

	class YARN_API KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(int keyCode)
			: KeyEvent(keyCode) {}

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "KeyTypededEvent: " << m_keyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	};

}