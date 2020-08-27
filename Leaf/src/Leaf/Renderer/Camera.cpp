#include "lfpch.h"
#include "Leaf/Renderer/Camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Leaf {
	
	Camera::Camera(const glm::mat4& projection)
		: m_Projection(projection), m_View(1.0f)
	{
		m_ViewProjection = m_Projection * m_View;
	}

	void Camera::UpdateViewProjectionMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Translation) *
			glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.w), { m_Rotation.x, m_Rotation.y, m_Rotation.z }) *
			glm::scale(glm::mat4(1.0f), m_Scale);

		m_View = glm::inverse(transform);

		m_ViewProjection = m_Projection * m_View;
	}

	void Camera::SetTranslation(const glm::vec3& translate)
	{
		m_Translation = translate;
		UpdateViewProjectionMatrix();
	}
	
	void Camera::SetRotation(float angle, const glm::vec3& axis)
	{
		m_Rotation = { axis, angle };
		UpdateViewProjectionMatrix();
	}
	
	void Camera::SetScale(const glm::vec3& scale)
	{
		m_Scale = scale;
		UpdateViewProjectionMatrix();
	}
	
	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float nearClip, float farClip)
		:Camera(glm::ortho(left, right, bottom, top, nearClip, farClip))
	{
	}

	void OrthographicCamera::SetProjection(float left, float right, float bottom, float top, float nearClip, float farClip)
	{
		m_Projection = glm::ortho(left, right, bottom, top, nearClip, farClip);
		m_ViewProjection = m_Projection * m_View;
	}

	void OrthographicCamera::SetRotation(float angle)
	{
		Camera::SetRotation(angle, { 0.0f,0.0f,1.0f });
	}
}