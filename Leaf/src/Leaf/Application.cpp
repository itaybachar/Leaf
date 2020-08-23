#include "lfpch.h"

#include "Leaf/Application.h"
#include "Leaf/Logger.h"
#include "Leaf/KeyCodes.h"

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

		//Load Triangle

		glCreateVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);

		float verts[12] = {
			-0.5f,0.0f,0.0f,
			0.5f,-0.0f,0.0f,
			0.0f,0.5f,0.0f,
			0.0f,-0.5f,0.0f
		};

		uint32_t ind[6] = {
		0,1,2,
		0,3,1
		};

		m_VertexBuffer.reset(VertexBuffer::Create(verts, sizeof(verts)));
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		m_IndexBuffer.reset(IndexBuffer::Create(ind, std::size(ind)));
	
		//Shader

		std::string vs = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			out vec3 o_Position;

			void main(){
				o_Position = a_Position;
				gl_Position = vec4(a_Position,1.0f);
			}
		)";

		std::string fs = R"(
		#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 o_Position;

			void main(){
				color = vec4(o_Position + 0.5,1);
			}
		)";

		m_Shader.reset(Shader::Create(vs, fs));
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
			glEnableVertexAttribArray(0);
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

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
		if (e.GetKeycode() == LF_KEY_B)
			m_Shader->Bind();

		if (e.GetKeycode() == LF_KEY_U)
			m_Shader->Unbind();

		return true;
	}
}

