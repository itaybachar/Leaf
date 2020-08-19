#pragma once
#include "Leaf/Events/IEvent.h"

namespace Leaf {

	struct WindowProps {
	public:
		WindowProps(std::string title = "Leaf Window", uint32_t width = 1280, uint32_t height = 720)
			: m_Title(title), m_Width(width), m_Height(height) {}

	public:
		std::string m_Title;
		uint32_t m_Width, m_Height;
	};

	class Window {
	public:
		using EventCallback = std::function<void(IEvent&)>;
		virtual ~Window() {};

		virtual void OnUpdate() = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallback& func) = 0;

		virtual void SetVSync(bool vsync) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() = 0;
	
		static Window* Create(const WindowProps& props = WindowProps());
	};
}