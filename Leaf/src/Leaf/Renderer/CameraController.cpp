#include "lfpch.h"

#include "Leaf/Core/Inputs.h"
#include "Leaf/Core/KeyCodes.h"

#include "Leaf/Renderer/CameraController.h"
#include "Leaf/Renderer/Renderer.h"

namespace Leaf {

	OrthographicCameraController::OrthographicCameraController(float aspect, bool rotate)
		: m_AspectRatio(aspect), m_Rotate(rotate), m_Camera(-m_AspectRatio*m_Zoom, m_AspectRatio * m_Zoom, -m_Zoom,m_Zoom)
	{
	}

	void OrthographicCameraController::OnUpdate(Timestep ts)
	{
		//Input Polling
		if (Inputs::IsKeyPressed(LF_KEY_W))
			m_CameraPosition.y += m_TranslationSpeed * ts;
		if (Leaf::Inputs::IsKeyPressed(LF_KEY_S))
			m_CameraPosition.y -= m_TranslationSpeed * ts;

		if (Leaf::Inputs::IsKeyPressed(LF_KEY_A))
			m_CameraPosition.x -= m_TranslationSpeed * ts;
		if (Leaf::Inputs::IsKeyPressed(LF_KEY_D))
			m_CameraPosition.x += m_TranslationSpeed * ts;

		m_Camera.SetTranslation(m_CameraPosition);

		if (m_Rotate) 
		{
			if (Leaf::Inputs::IsKeyPressed(LF_KEY_Q))
				m_CameraRotation += m_RotationSpeed * ts;
			if (Leaf::Inputs::IsKeyPressed(LF_KEY_E))
				m_CameraRotation -= m_RotationSpeed * ts;

			m_Camera.SetRotation(m_CameraRotation);
		}
	}

	void OrthographicCameraController::OnEvent(IEvent& e)
	{
		EventDispatcher disp(e);
		disp.DispatchEvent<WindowResizeEvent>(BIND_EVENT_FN(OrthographicCameraController::OnWindowResize));
		disp.DispatchEvent<MouseScrollEvent>(BIND_EVENT_FN(OrthographicCameraController::OnMouseScroll));
	}

	bool OrthographicCameraController::OnWindowResize(WindowResizeEvent& e)
	{
		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();

		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		m_Camera.SetProjection(-m_AspectRatio * m_Zoom, m_AspectRatio * m_Zoom, -m_Zoom, m_Zoom);
		return false;
	}

	bool OrthographicCameraController::OnMouseScroll(MouseScrollEvent& e)
	{
		m_Zoom -= e.GetYOffset() * 0.25f;
		m_Zoom = std::fmax(0.25f,m_Zoom);

		//Normalize move speed based on zoom
		m_TranslationSpeed = (m_Zoom<1)? m_Zoom*1.25f:m_Zoom;

		m_Camera.SetProjection(-m_AspectRatio * m_Zoom, m_AspectRatio * m_Zoom, -m_Zoom, m_Zoom);

		return false;
	}

}

