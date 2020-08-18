#pragma once
#include "lfpch.h"
#include "Leaf/Core.h"

namespace Leaf {

	//Blokcing Event

	//Event Types
	enum class EventType {
		None = 0,
		OnWindowResize, OnWindowClose, OnWindowFocus, OnWindowLostFocus,
		OnMouseButtonPress, OnMouseButtonRelease, OnMouseMove, OnMouseScroll,
		OnKeyPress, OnKeyRelease,
		OnAppTick, OnAppUpdate, OnAppRender
	};

	//Event Categories to filter events
	enum EventCategory {
		None = 0,
		ApplicationEvent = BIT(0),
		InputEvent = BIT(1),
		MouseEvent = BIT(2), MouseBEvent = BIT(3),
		KeyboardEvent = BIT(4)
	};

	//Base Event Interface
	class LEAF_API IEvent {
		friend class EventDispatcher;
	public:
		
		//Type
		virtual EventType GetEventType() const = 0;
		static EventType GetStaticEventType();

		//Category
		virtual int GetCategory() const = 0;

		//Debugging
		virtual const char* GetName() const = 0;
		inline virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category) {
			return GetCategory() & category;
		}

		inline bool IsHandled() const {
			return m_IsHandled;
		}

	protected:
		bool m_IsHandled;
	};

	//WINDOWS SPECIFIC
	//Macros to simplify Event implementation code
#define SET_EVENT_TYPE(type) static EventType GetStaticEventType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticEventType(); }\
								virtual const char* GetName() const override { return #type; }
									
#define SET_EVENT_CATEGORY(category) virtual int32_t GetCategory() const override{ return category; }

	//Event Dispatcher Class
	//Handles wether the event will call on a callback
	class EventDispatcher {
	public:
		template<typename T>
		using EventCallback = std::function<bool(T&)>;

	public:
		EventDispatcher(IEvent& e)
			: m_Event(e) {}

		template<typename T>
		bool DispatchEvent(EventCallback<T> callback)
		{
			//Check if the event matches the input static type
			if (m_Event.GetEventType() == T::GetStaticEventType()) {
				m_Event.m_IsHandled = callback(*(T*)&m_Event);

				//Callback was called
				return true;
			}

			//Callback was not called
			return false;
		}

	private:
		IEvent& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const IEvent& e) {
		return os << e.ToString();
	}
}