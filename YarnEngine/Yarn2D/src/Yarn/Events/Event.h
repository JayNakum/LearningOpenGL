#pragma once

#include "YarnPCH.h"

#include "Yarn/Core.h"

namespace Yarn {
	// Events in Yarn are currently blocking.
	// Meaning when an event occures it is immediately fealt with right away.

	// There are 3 basic event types under which all the Events fall.
	// AppEvent & WindowEvent, KeyEvent and MouseEvent
	// [EventType] enum contains all the event type supported by Yarn.
	enum class EventType 
	{
		None = 0,
		AppTick, AppUpdate, AppRender,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	// EventCategory is a flag 
	// [BIT] field defined in [Core.h] is used to manage multiple categories.
	// So for example a MouseButtonPressed event falls under 3 categories
	// EventCategoryMouseButton, EventCategoryMouse and EventCategoryInput.
	enum EventCategory
	{
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput       = BIT(1),
		EventCategoryKeyboard    = BIT(2),
		EventCategoryMouse       = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};

	// [Event] class is a base class for all events.
	// It contains necessary virtual and pure virtual functions 
	// that needs to be implemented its sub classes.
	// Every other event extends this class.
	class YARN_API Event
	{
		friend class EventDispatcher;
	public:
		// m_isHandled is a variable that determines wheather the event needs
		// to be handled by the child layers or not.
		// So as long as m_isHandled is false it would mean that
		// a child layer needs to do something with the event. 
		bool m_isHandled = false;

		virtual EventType getEventType() const = 0;
		virtual const char* getEventName() const = 0;
		virtual int getEventCategoryFlags() const = 0;
		virtual std::string toString() const { return getEventName(); }

		inline bool isInCategory(EventCategory category)
		{
			return getEventCategoryFlags() & category;
		}

	};

// As we have pure virtual functions in oue event class
// instead of overriding each function every time
// here we are defining macros that will fill in the blanks and override the function.
#define EVENT_CLASS_TYPE(type) static EventType getStaticEventType() { return EventType::##type; }\
							   virtual EventType getEventType() const override { return getStaticEventType(); }\
							   virtual const char* getEventName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int getEventCategoryFlags() const override { return category; }


	// The dispatcher is a way for us to dispatch an event based on their type
	class EventDispatcher
	{
		template<typename T>
		using EventFunction = std::function<bool(T&)>;

	public:
		EventDispatcher(Event& event)
			: m_event(event) {}

		template<typename T>
		bool dispatch(EventFunction<T> function)
		{
			if (m_event.getEventType() == T::getStaticEventType())
			{
				m_event.m_isHandled = function(*(T*)&m_event);
				return true;
			}
			return false;
		}

	private:
		Event& m_event;
	};

	// This operator overload is for the logging library
	// It allows us to call toString on the event
	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.toString();
	}

}