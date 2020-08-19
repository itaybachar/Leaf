#pragma once
#include "Leaf/Layer.h"

#include "Leaf/Events/MouseEvent.h"
#include "Leaf/Events/KeyEvent.h"
#include "Leaf/Events/ApplicationEvent.h"

namespace Leaf {
	class LEAF_API ImGuiLayer : public Layer {
	public:
		ImGuiLayer ()
			: Layer("ImGui Layer"), m_Time(0) {}
		
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void OnUpdate() override;
		virtual void OnEvent(IEvent& e) override;

		bool OnMousePress(MouseButtonPressEvent& e);
		bool OnMouseRelease(MouseButtonReleaseEvent& e);
		bool OnMouseMove(MouseMoveEvent& e);
		bool OnMouseScroll(MouseScrollEvent& e);

		bool OnKeyPress(KeyPressEvent& e);
		bool OnKeyRelease(KeyReleaseEvent& e);
		bool OnKeyTyped(KeyTypedEvent& e);

		bool OnResize(WindowResizeEvent& e);

	private:
		double m_Time;
	};
}