#pragma once
#include "Leaf/Events/IEvent.h"

namespace Leaf {

	//Base key event class, virtual
	class LEAF_API KeyEvent : public IEvent {
	public:
		inline int GetKeycode() { return m_Keycode; }

		//Category
		SET_EVENT_CATEGORY(EventCategory::InputEvent | EventCategory::KeyboardEvent)
	protected:
		KeyEvent(int32_t keycode)
			: m_Keycode(keycode) {}

	protected:
		int32_t m_Keycode;
	};

	//KeyPress Event
	class LEAF_API KeyPressEvent : public KeyEvent {

	public:
		KeyPressEvent(int32_t keycode, int32_t repeat)
			: KeyEvent(keycode), m_RepeatCount(repeat) {}

		//Debugging
		virtual std::string ToString() const override{
			std::stringstream s;
			s << "Key Pressed: " << m_Keycode << ", Repeat: " << m_RepeatCount;
			return s.str();
		};

		SET_EVENT_TYPE(OnKeyPress)

	private:
		int32_t m_RepeatCount;
	};

	//KeyRelease Event
	class LEAF_API KeyReleaseEvent : public KeyEvent {

	public:
		KeyReleaseEvent(int32_t keycode)
			: KeyEvent(keycode) {}

		//Debugging
		virtual std::string ToString() const override {
			std::stringstream s;
			s << "Key Released: " << m_Keycode;
			return s.str();
		};

		SET_EVENT_TYPE(OnKeyRelease)
	};

	//KeyTyped Event
	class LEAF_API KeyTypedEvent : public KeyEvent {

	public:
		KeyTypedEvent(uint32_t keycode)
			: KeyEvent(keycode) {}

		//Debugging
		virtual std::string ToString() const override {
			std::stringstream s;
			s << "Key Typed: " << m_Keycode;
			return s.str();
		};

		SET_EVENT_TYPE(OnKeyTyped)
	};

}