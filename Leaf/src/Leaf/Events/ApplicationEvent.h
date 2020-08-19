#pragma once
#include "Leaf/Events/IEvent.h"

namespace Leaf {
	
	class LEAF_API WindowResizeEvent : public IEvent {
	public:
		WindowResizeEvent(uint32_t width, uint32_t height)
			: m_Width(width), m_Height(height) {}

		inline std::string ToString() const override {
			std::stringstream s;

			s << "Window Resized: (" << m_Width << ", " << m_Height << ")";
			
			return s.str();
		}

		inline float GetHeight() const { return m_Height; }
		inline float GetWidth() const { return m_Width; }

		SET_EVENT_TYPE(OnWindowResize)
		SET_EVENT_CATEGORY(ApplicationEvent)
	private:
		uint32_t m_Width;
		uint32_t m_Height;
	};

	class LEAF_API WindowCloseEvent : public IEvent {
	public:
		WindowCloseEvent() {}

		inline std::string ToString() const override {
			return "Window Closed";
		}

		SET_EVENT_TYPE(OnWindowClose)
		SET_EVENT_CATEGORY(ApplicationEvent)
	};

	class LEAF_API WindowFocusEvent : public IEvent {
	public:

		WindowFocusEvent() {}

		inline std::string ToString() const override {
			return "Window Gained Focused";
		}

		SET_EVENT_TYPE(OnWindowFocus)
		SET_EVENT_CATEGORY(ApplicationEvent)
	};

	class LEAF_API WindowLostFocusEvent : public IEvent {
	public:
		WindowLostFocusEvent() {}

		inline std::string ToString() const override {
			return "Window Lost Focus";
		}

		SET_EVENT_TYPE(OnWindowLostFocus)
		SET_EVENT_CATEGORY(ApplicationEvent)
	};

	class LEAF_API AppTickEvent : public IEvent {
	public:
		AppTickEvent() {}

		inline std::string ToString() const override {
			return "App Ticked";
		}

		SET_EVENT_TYPE(OnAppTick)
		SET_EVENT_CATEGORY(ApplicationEvent)
	};

	class LEAF_API AppRenderEvent : public IEvent {
	public:
		AppRenderEvent() {}

		inline std::string ToString() const override {
			return "App Rendered";
		}

		SET_EVENT_TYPE(OnAppRender)
		SET_EVENT_CATEGORY(ApplicationEvent)
	};

	class LEAF_API AppUpdateEvent : public IEvent {
	public:
		AppUpdateEvent() {}

		inline std::string ToString() const override {
			return "App Updated";
		}

		SET_EVENT_TYPE(OnAppUpdate)
		SET_EVENT_CATEGORY(ApplicationEvent)
	};
}