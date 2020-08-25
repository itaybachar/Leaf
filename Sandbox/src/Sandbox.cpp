#include <Leaf.h>
#include <ImGui/imgui.h>

class ExampleLayer : public Leaf::Layer {
public:
	ExampleLayer(const std::string name)
		: Leaf::Layer(name) , m_Camera(Leaf::OrthographicCamera(-1.78f, 1.78f, -1.0f, 1.0f))
	{
		//Diamond
		#pragma region Diamond
		float diamond[4 * 7] = {
			-0.5f,0.0f,0.0f, 0.8f, 0.2f, 0.2f, 1.0f,
			0.5f,-0.0f,0.0f, 0.2f, 0.8f, 0.3f, 1.0f,
			0.0f,0.5f,0.0f,  0.3f, 0.2f, 0.8f, 1.0f,
			0.0f,-0.75f,0.0f, 0.8f, 0.8f, 0.8f, 1.0f
		};

		uint32_t diamondInd[6] = {
		0,1,2,
		0,3,1
		};

		m_VArray.reset(Leaf::VertexArray::Create());

		std::shared_ptr<Leaf::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Leaf::VertexBuffer::Create(diamond, sizeof(diamond)));

		Leaf::BufferLayout layout = {
			{Leaf::ShaderDataType::Float3, "a_Position"},
			{Leaf::ShaderDataType::Float4, "a_Color"}
		};

		vertexBuffer->SetLayout(layout);
		m_VArray->AddVertexBuffer(vertexBuffer);

		std::shared_ptr<Leaf::IndexBuffer> indexBuffer;
		indexBuffer.reset(Leaf::IndexBuffer::Create(diamondInd, (uint32_t)std::size(diamondInd)));
		m_VArray->SetIndexBuffer(indexBuffer);
		#pragma endregion

		//Test 2
		#pragma region Backdrop
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

		m_SquareVA.reset(Leaf::VertexArray::Create());

		vertexBuffer.reset(Leaf::VertexBuffer::Create(square, sizeof(square)));

		layout = {
			{Leaf::ShaderDataType::Float3, "a_Position"}
		};

		vertexBuffer->SetLayout(layout);
		m_SquareVA->AddVertexBuffer(vertexBuffer);

		indexBuffer.reset(Leaf::IndexBuffer::Create(squareInd, (uint32_t)std::size(squareInd)));
		m_SquareVA->SetIndexBuffer(indexBuffer);
		#pragma endregion
		
		//Shader
		#pragma region Shader
		std::string vs = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;

			void main(){
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position,1.0f);
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

			uniform mat4 u_ViewProjection;			

			out vec3 v_Position;

			void main(){
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position,1.0f);
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

		m_Shader.reset(Leaf::Shader::Create(vs, fs));
		m_SolidShader.reset(Leaf::Shader::Create(solidVS, solidFS));
#pragma endregion
	}

	virtual void OnAttach() override {
	}
	virtual void OnDetach() override {
	}

	virtual void OnUpdate(Leaf::Timestep ts) override {

		LF_INFO("Delta Time {0}s [{1}ms]", ts.GetTime(), ts.GetTimeMili());

		//Input Polling
		if (Leaf::Inputs::IsKeyPressed(LF_KEY_UP))
			m_Ty += m_CameraSpeed * ts;
		if (Leaf::Inputs::IsKeyPressed(LF_KEY_DOWN))
			m_Ty -= m_CameraSpeed * ts;
		
		if (Leaf::Inputs::IsKeyPressed(LF_KEY_LEFT))
			m_Tx -= m_CameraSpeed * ts;
		if (Leaf::Inputs::IsKeyPressed(LF_KEY_RIGHT))
			m_Tx += m_CameraSpeed * ts;

		if (Leaf::Inputs::IsKeyPressed(LF_KEY_A))
			m_Rot += m_CameraSpeedRot * ts;
		if (Leaf::Inputs::IsKeyPressed(LF_KEY_D))
			m_Rot -= m_CameraSpeedRot * ts;

		m_Camera.SetRotate(m_Rot, { 0.0f,0.0f,1.0f });
		m_Camera.SetTranslation({ m_Tx,m_Ty,0.0f });

		Leaf::Renderer::BeginScene(m_Camera);
		Leaf::Renderer::Submit(m_SolidShader, m_SquareVA);
		Leaf::Renderer::Submit(m_Shader, m_VArray);
		Leaf::Renderer::EndScene();
	}

	virtual void OnImGuiUpdate() override {
	}
	
	virtual void OnEvent(Leaf::IEvent& e) override {
		
	}
private:
	std::shared_ptr<Leaf::Shader> m_Shader;
	std::shared_ptr<Leaf::VertexArray> m_VArray;
					
	std::shared_ptr<Leaf::Shader> m_SolidShader;
	std::shared_ptr<Leaf::VertexArray> m_SquareVA;

	Leaf::Camera m_Camera;

	float m_Tx = 0.0f, m_Ty = 0.0f, m_Rot = 0.0f;
	float m_CameraSpeed = 3.0f;
	float m_CameraSpeedRot = 180.0f;
};					

class Sandbox : public Leaf::Application
{
public:
	Sandbox() {
		PushLayer(new ExampleLayer("Layer1"));
	}
	~Sandbox() {}
};

Leaf::Application* Leaf::CreateLeaf() {
	
	return new Sandbox();
}