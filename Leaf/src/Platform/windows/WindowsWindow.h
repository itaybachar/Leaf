#pragma once
#include "Leaf/Core/Window.h"
#include "Leaf/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Leaf {

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow() override;

		virtual void OnUpdate() override;

		inline virtual uint32_t GetWidth() const override {
			return m_Data.m_Width;
		}

		inline virtual uint32_t GetHeight() const override {
			return m_Data.m_Height;
		}

		inline virtual void SetEventCallback(const EventCallback& func) override {
			m_Data.callback = func;
		}

		virtual void SetVSync(bool vsync) override;

		inline virtual bool IsVSync() const override {
			return m_Data.VSync;
		};

		virtual void* GetNativeWindow() override {
			return (void*)m_Window;
		}

	private:
		void Init(const WindowProps& props);
		void Shutdown();

	private:
		GLFWwindow* m_Window;
		GraphicsContext* m_Context;

		struct Data {
			std::string m_Title;
			uint32_t m_Width, m_Height;
			bool VSync;

			EventCallback callback;
		};

		Data m_Data;
	};
}
