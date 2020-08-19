#pragma once
#include "Leaf/Layer.h"

namespace Leaf {
	class LEAF_API ImGuiLayer : public Layer {
	public:
		ImGuiLayer ()
			: Layer("ImGui Layer"), m_Time(0) {}
		
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiUpdate() override;

		//Starts and Ends setup for rendering ImGui, all draw calls will be called between begin and end
		void Begin();
		void End();
	private:
		double m_Time;
	};
}