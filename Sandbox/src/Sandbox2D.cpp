#include "Sandbox2D.h"

#include <Leaf/Core/EntryPoint.h>
#include <ImGui/imgui.h>
#include <Platform/OpenGL/OpenGLShader.h>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{
}

void Sandbox2D::OnAttach()
{
	float square[4 * 3] = {
			-0.50f,-0.50f,0.0f,
			0.50f,-0.50f,0.0f,
			0.50f,0.50f,0.0f,
			-0.50f,0.50f,0.0f
	};

	uint32_t squareInd[6] = {
	0,1,2,
	0,2,3
	};

	m_SquareVA = Leaf::VertexArray::Create();

	Leaf::Ref<Leaf::VertexBuffer> vertexBuffer = Leaf::VertexBuffer::Create(square, sizeof(square));

	Leaf::BufferLayout layout = {
		{Leaf::ShaderDataType::Float3, "a_Position"}
	};

	vertexBuffer->SetLayout(layout);
	m_SquareVA->AddVertexBuffer(vertexBuffer);

	Leaf::Ref<Leaf::IndexBuffer> indexBuffer = Leaf::IndexBuffer::Create(squareInd, (uint32_t)std::size(squareInd));
	m_SquareVA->SetIndexBuffer(indexBuffer);

	m_FlatColorShader = Leaf::Shader::Create("assets/shaders/FlatColor.glsl");
}

void Sandbox2D::OnDetach()
{
	//Nothing here
}

void Sandbox2D::OnUpdate(Leaf::Timestep ts)
{
	m_CameraController.OnUpdate(ts);

	Leaf::Renderer::BeginScene(m_CameraController.GetCamera());

	//Upload Color
	m_FlatColorShader->Bind();
	std::dynamic_pointer_cast<Leaf::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_Color);


	// glm::scale(glm::mat4(1), glm::vec3(1.125f, 2.0f, 0.0f))
	Leaf::Renderer::Submit(m_FlatColorShader, m_SquareVA);

	Leaf::Renderer::EndScene();
}

void Sandbox2D::OnImGuiUpdate()
{
	ImGui::Begin("Checker Window");

	ImGui::Text("This is some useful text.");

	ImGui::ColorEdit4("MyColor##1", (float*)&m_Color);

	ImGui::NewLine();

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();
}

void Sandbox2D::OnEvent(Leaf::IEvent& e)
{
	m_CameraController.OnEvent(e);
}
