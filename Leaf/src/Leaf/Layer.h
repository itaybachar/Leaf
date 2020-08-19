#pragma once
#include "Leaf/Core.h"
#include "Leaf/Events/IEvent.h"

namespace Leaf {
	class LEAF_API Layer
	{
	public:
		Layer(const std::string name = "Layer");

		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}

		virtual void OnUpdate() {}
		virtual void OnImGuiUpdate() {}
		virtual void OnEvent(IEvent& e) {}

		inline const std::string& GetName() const { return m_Name; };

	private:
		std::string m_Name;
	};
}

