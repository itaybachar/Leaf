#pragma once
#include "Leaf/Events/IEvent.h"

namespace Leaf {

	//Mouse Moved Event
	class LEAF_API MouseMoveEvent : public IEvent {
	public:
		MouseMoveEvent(float xPos, float yPos)
			: m_XPosition(xPos), m_YPosition(yPos) {}

		inline std::string ToString() const override {
			std::stringstream s;
			s << "Mouse Moved, X: " << m_XPosition << " Y: " << m_YPosition;
			
			return s.str();
		}

		inline float GetX() const {
			return m_XPosition;
		}

		inline float GetY() const {
			return m_YPosition;
		}

		SET_EVENT_TYPE(OnMouseMove)
		SET_EVENT_CATEGORY(MouseEvent | InputEvent)

	private:
		float m_XPosition;
		float m_YPosition;
	};

	//Mouse Scroll Event
	class LEAF_API MouseScrollEvent : public IEvent {
	public:
		MouseScrollEvent(float xOff, float yOff)
			: m_XOffset(xOff), m_YOffset(yOff) {}
		
		inline std::string ToString() const override {
			std::stringstream s;
			s << "Mouse Scroll, X Offset: " << m_XOffset << " Y Offset: " << m_YOffset;

			return s.str();
		}

		inline float GetXOffset() const {
			return m_XOffset;
		}

		inline float GetYOffset() const {
			return m_YOffset;
		}

		SET_EVENT_TYPE(OnMouseScroll)
		SET_EVENT_CATEGORY(MouseEvent | InputEvent)

	private:
		float m_XOffset;
		float m_YOffset;
	};

	
	//Mouse Button Events
	class LEAF_API MouseButtonEvent : public IEvent {
	public:
		inline int32_t GetMouseButton() const { return m_Button; }

		SET_EVENT_CATEGORY(MouseBEvent | MouseEvent | InputEvent)
	protected:
		MouseButtonEvent(int32_t button)
			: m_Button(button) {}

		int32_t m_Button;
	};

	class LEAF_API MouseButtonPressEvent : public MouseButtonEvent {
	public:
		MouseButtonPressEvent(int32_t button)
			: MouseButtonEvent(button) {}

		virtual std::string ToString() const override {
			std::stringstream s;
			s << "MouseButtonPressed: " << m_Button;
			return s.str();
		}

		SET_EVENT_TYPE(OnMouseButtonPress)
	};

	class LEAF_API MouseButtonReleaseEvent : public MouseButtonEvent {
	public:
		MouseButtonReleaseEvent(int32_t button)
			: MouseButtonEvent(button) {}

		virtual std::string ToString() const override {
			std::stringstream s;
			s << "MouseButtonReleased: " << m_Button;
			return s.str();
		}

		SET_EVENT_TYPE(OnMouseButtonRelease)
	};
	
}