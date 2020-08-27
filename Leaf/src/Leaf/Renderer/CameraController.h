#pragma once
#include "Leaf/Core/Timestep.h"

#include "Leaf/Renderer/Camera.h"

#include "Leaf/Events/ApplicationEvent.h"
#include "Leaf/Events/MouseEvent.h"


namespace Leaf {
	class OrthographicCameraController {
	public:
		OrthographicCameraController(float aspect, bool rotate = false);

		void OnUpdate(Timestep ts);
		void OnEvent(IEvent& e);

		inline OrthographicCamera& GetCamera() { return m_Camera; }
		inline const OrthographicCamera& GetCamera() const { return m_Camera; }

	private:
		bool OnWindowResize(WindowResizeEvent& e);

		bool OnMouseScroll(MouseScrollEvent& e);
	private:
		float m_AspectRatio;
		float m_Zoom = 1.0f;
		bool m_Rotate;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f;

		float m_TranslationSpeed = 5.0f;
		float m_RotationSpeed = 180.0f;

		OrthographicCamera m_Camera;
	};
}