#pragma once
#include <Leaf.h>

#include <glm/glm.hpp>

class Sandbox2D : public Leaf::Layer {
public:
	Sandbox2D();
	~Sandbox2D() = default;


	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(Leaf::Timestep ts) override;
	virtual void OnImGuiUpdate() override;
	virtual void OnEvent(Leaf::IEvent& e) override;

private:
	Leaf::Ref<Leaf::VertexArray> m_SquareVA;
	Leaf::Ref<Leaf::Shader> m_FlatColorShader;
	
	Leaf::OrthographicCameraController m_CameraController;

	glm::vec4 m_Color = glm::vec4(1.0f);
};