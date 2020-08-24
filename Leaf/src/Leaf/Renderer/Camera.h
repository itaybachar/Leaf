#pragma once
#include <glm/glm.hpp>

namespace Leaf {

	class Camera {
	public:
		virtual ~Camera() {};

		void SetTranslation(const glm::vec3& translate);
		void SetRotate(float angle, const glm::vec3& axis);
		void SetScale(const glm::vec3& scale);

		inline const glm::mat4& GetProjection() const { return m_Projection; }
		inline const glm::mat4& GetView() const { return m_View; }
		inline const glm::mat4& GetViewProjection() const { return m_ViewProjection; }
	protected:
		Camera(const glm::mat4& projection);

		glm::mat4 m_Projection;
		glm::mat4 m_View;
		glm::mat4 m_ViewProjection;

		glm::vec3 m_Translation = { 0.0f, 0.0f ,0.0f };
		glm::vec4 m_Rotation = { 1.0f, 1.0f, 1.0f, 0.0f }; //axis(x,y,z) angle(deg)
		glm::vec3 m_Scale = { 1.0f, 1.0f, 1.0f };
	private:
		void UpdateViewProjectionMatrix();
	};

	class OrthographicCamera : public Camera {
	public:
		OrthographicCamera(float width, float height)
			: OrthographicCamera(-width / 2, width / 2, -height / 2, height / 2) {}

		OrthographicCamera(float left, float right, float bottom, float top, float nearClip = 1, float farClip = -1);
	};
}