#include "lfpch.h"

#include "Leaf/Application.h"
#include "Leaf/Logger.h"
#include "Leaf/KeyCodes.h"
#include "Leaf/Inputs.h"

#include <glad/glad.h>

namespace Leaf {
	Application* Application::s_Instance = nullptr;

	
	Application::Application()
	{
		LF_ASSERT(!s_Instance, "Application is already created!");
		s_Instance = this;

		m_Leaf = std::unique_ptr<Window>(Window::Create());
		m_Leaf->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
		m_IsRunning = true;

		//Create ImGui Layer
		m_ImGuiLayer = new ImGuiLayer();
		m_Layers.PushOverlay(m_ImGuiLayer);

		//Test Renders
		float diamond[4 * 7] = {
			-0.5f,0.0f,0.0f, 0.8f, 0.2f, 0.2f, 1.0f,
			0.5f,-0.0f,0.0f, 0.2f, 0.8f, 0.3f, 1.0f,
			0.0f,0.5f,0.0f,  0.3f, 0.2f, 0.8f, 1.0f,
			0.0f,-0.5f,0.0f, 0.8f, 0.8f, 0.8f, 1.0f
		};

		uint32_t diamondInd[6] = {
		0,1,2,
		0,3,1
		};

		m_VArray.reset(VertexArray::Create());

		std::shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::Create(diamond, sizeof(diamond)));

		BufferLayout layout = {
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float4, "a_Color"}
		};

		vertexBuffer->SetLayout(layout);
		m_VArray->AddVertexBuffer(vertexBuffer);

		std::shared_ptr<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(diamondInd, std::size(diamondInd)));
		m_VArray->SetIndexBuffer(indexBuffer);

		//Test 2
		float square[4 * 3] = {
			-0.75f,-0.75f,0.0f,
			0.75f,-0.75f,0.0f,
			0.75f,0.75f,0.0f, 
			-0.75f,0.75f,0.0f,
		};

		uint32_t squareInd[6] = {
		0,1,2,
		0,2,3
		};

		m_SquareVA.reset(VertexArray::Create());

		vertexBuffer.reset(VertexBuffer::Create(square, sizeof(square)));

		layout = {
			{ShaderDataType::Float3, "a_Position"}
		};

		vertexBuffer->SetLayout(layout);
		m_SquareVA->AddVertexBuffer(vertexBuffer);

		indexBuffer.reset(IndexBuffer::Create(squareInd, std::size(squareInd)));
		m_SquareVA->SetIndexBuffer(indexBuffer);

		//Shader

		std::string vs = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			out vec3 v_Position;
			out vec4 v_Color;

			void main(){
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = vec4(a_Position,1.0f);
			}
		)";

		std::string fs = R"(
		#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			in vec4 v_Color;

			void main(){
				color = vec4(v_Position + 0.5,1);
				color = v_Color;
			}
		)";

		std::string solidVS = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			out vec3 v_Position;

			void main(){
				v_Position = a_Position;
				gl_Position = vec4(a_Position,1.0f);
			}
		)";

		std::string solidFS = R"(
		#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;

			void main(){
				color = vec4(v_Position + 0.5,1);
				color = vec4(0.8,0.2,0.2,1);
			}
		)";

		m_Shader.reset(Shader::Create(vs, fs));
		m_SolidShader.reset(Shader::Create(solidVS, solidFS));
	}

	Application::~Application()
	{
	}

	void Application::OnEvent(IEvent& e)
	{
		for (auto it = m_Layers.end(); it != m_Layers.begin();) {
			(*--it)->OnEvent(e);
			if (e.m_IsHandled)
				break;
		}

		//Window Close
		EventDispatcher handler(e);
		handler.DispatchEvent<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
		handler.DispatchEvent<WindowResizeEvent>(BIND_EVENT_FN(Application::OnWindowResize));
		handler.DispatchEvent<KeyPressEvent>(BIND_EVENT_FN(Application::OnKeyPress));

	}

	void Application::Run()
	{
		//Render Loop
		while (m_IsRunning) {

			//Clear Buffers
			glClearColor(0.15f, 0.15f, 0.15f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			//Render Elemets
			m_SolidShader->Bind();
			m_SquareVA->Bind();
			glDrawElements(GL_TRIANGLES, m_SquareVA->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

			m_Shader->Bind();
			m_VArray->Bind();
			glDrawElements(GL_TRIANGLES, m_VArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

			//Render normal opengl first
			for (Layer* l : m_Layers) {
				l->OnUpdate();
			}

			//Render ImGui
			m_ImGuiLayer->Begin();
			for (Layer* l : m_Layers) {
				l->OnImGuiUpdate();
			}
			m_ImGuiLayer->End();

			m_Leaf->OnUpdate();
		}
	}
	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_IsRunning = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		glViewport(0, 0, e.GetWidth(), e.GetHeight());
		return true;
	}
	bool Application::OnKeyPress(KeyPressEvent& e)
	{
		if (e.GetKeycode() == LF_KEY_KP_1) {
			if(Inputs::IsKeyPressed(LF_KEY_LEFT_ALT))
				m_SolidShader->Unbind();
			else
				m_SolidShader->Bind();
		}

		if (e.GetKeycode() == LF_KEY_KP_2) {
			if (Inputs::IsKeyPressed(LF_KEY_LEFT_ALT))
				m_Shader->Unbind();
			else
				m_Shader->Bind();
		}

		return true;
	}
}

