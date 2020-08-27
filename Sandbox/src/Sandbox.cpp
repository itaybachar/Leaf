#include <Leaf.h>
#include <ImGui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <Platform/OpenGL/OpenGLShader.h>

class ExampleLayer : public Leaf::Layer {
public:
	ExampleLayer(const std::string name)
		: Leaf::Layer(name) , m_CameraController(1280.0f/720.0f)
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

		m_VArray = Leaf::VertexArray::Create();

		Leaf::Ref<Leaf::VertexBuffer> vertexBuffer;
		vertexBuffer = Leaf::VertexBuffer::Create(diamond, sizeof(diamond));

		Leaf::BufferLayout layout = {
			{Leaf::ShaderDataType::Float3, "a_Position"},
			{Leaf::ShaderDataType::Float4, "a_Color"}
		};

		vertexBuffer->SetLayout(layout);
		m_VArray->AddVertexBuffer(vertexBuffer);

		Leaf::Ref<Leaf::IndexBuffer> indexBuffer;
		indexBuffer = Leaf::IndexBuffer::Create(diamondInd, (uint32_t)std::size(diamondInd));
		m_VArray->SetIndexBuffer(indexBuffer);
		#pragma endregion

		//Test 2
		#pragma region Backdrop
		float square[4 * 5] = {
			-0.50f,-0.50f,0.0f, 0.0f, 0.0f,
			0.50f,-0.50f,0.0f,  1.0f, 0.0f,
			0.50f,0.50f,0.0f,   1.0f, 1.0f,
			-0.50f,0.50f,0.0f,  0.0f, 1.0f
		};

		uint32_t squareInd[6] = {
		0,1,2,
		0,2,3
		};

		m_SquareVA = Leaf::VertexArray::Create();

		vertexBuffer = Leaf::VertexBuffer::Create(square, sizeof(square));

		layout = {
			{Leaf::ShaderDataType::Float3, "a_Position"},
			{Leaf::ShaderDataType::Float2, "a_TexCoord"}
		};

		vertexBuffer->SetLayout(layout);
		m_SquareVA->AddVertexBuffer(vertexBuffer);

		indexBuffer = Leaf::IndexBuffer::Create(squareInd, (uint32_t)std::size(squareInd));
		m_SquareVA->SetIndexBuffer(indexBuffer);
		#pragma endregion
		
		//Shader
		#pragma region Shader
		std::string vs = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main(){
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position,1.0f);
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

		std::string flatColorvs = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;		

			void main(){
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position,1.0f);
			}
		)";

		std::string flatColorfs = R"(
		#version 330 core
			
			layout(location = 0) out vec4 color;

			uniform vec4 u_Color;

			void main(){
				color = u_Color;
			}
		)";

		m_ShaderMan.Add(Leaf::Shader::Create("Diamond",vs, fs));
		m_ShaderMan.Add(Leaf::Shader::Create("FlatColor",flatColorvs, flatColorfs));
		m_ShaderMan.Load("assets/shaders/Texture.glsl");
#pragma endregion

		m_Texture = Leaf::Texture2D::Create(tex[0]);
		m_Texture->Bind();

		auto& shader = m_ShaderMan.Get("Texture");
		std::dynamic_pointer_cast<Leaf::OpenGLShader>(shader)->Bind();
		std::dynamic_pointer_cast<Leaf::OpenGLShader>(shader)->UploadUniformFloat("u_Texture", 0);
	}

	virtual void OnAttach() override {
	}
	virtual void OnDetach() override {
	}

	virtual void OnUpdate(Leaf::Timestep ts) override {

		m_CameraController.OnUpdate(ts);

		glm::mat4 scale = glm::scale(glm::mat4(1), glm::vec3(0.1f));

		Leaf::Renderer::BeginScene(m_CameraController.GetCamera());

		int gridSize = 20;
		auto& shader = m_ShaderMan.Get("FlatColor");
		shader->Bind();
		for (int y = 0; y < gridSize; y++)
		{

			for (int x = 0; x < gridSize; x++)
			{
				glm::mat4 transform = glm::translate(glm::mat4(1), { x * 0.11f, y * 0.11f, 1.0f }) * scale;
				if ((x+y) % 2 == 0)
					std::dynamic_pointer_cast<Leaf::OpenGLShader>(shader)->UploadUniformFloat4("u_Color",m_ColorA);
				else
					std::dynamic_pointer_cast<Leaf::OpenGLShader>(shader)->UploadUniformFloat4("u_Color", m_ColorB);
				
				Leaf::Renderer::Submit(shader, m_SquareVA,transform);
			}
		}
		
		//Texture
		//m_Texture->Bind();
		shader = m_ShaderMan.Get("Texture");
		Leaf::Renderer::Submit(shader, m_SquareVA, glm::scale(glm::mat4(1), glm::vec3(1.5f)));

		//Diamond
		//Leaf::Renderer::Submit(m_Shader, m_VArray);
		Leaf::Renderer::EndScene();
	}

	virtual void OnImGuiUpdate() override {
		ImGui::Begin("Checker Window");            

		ImGui::Text("This is some useful text."); 

		ImGui::ColorEdit4("MyColor##1", (float*)&m_ColorA);
		ImGui::ColorEdit4("MyColor##2", (float*)&m_ColorB);

		ImGui::NewLine();

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}
	
	virtual void OnEvent(Leaf::IEvent& e) override {
		m_CameraController.OnEvent(e);

		Leaf::EventDispatcher disp(e);
		disp.DispatchEvent<Leaf::KeyPressEvent>(BIND_EVENT_FN(ExampleLayer::SwapTex));
	}

	bool ExampleLayer::SwapTex(Leaf::KeyPressEvent& e) {
		if (e.GetKeycode() == LF_KEY_ENTER) {
			index++;
			m_Texture = Leaf::Texture2D::Create(tex[index % 4]);
			m_Texture->Bind();
		}
		
		return true;
	}

private:

	std::string tex[4] = {
		"assets/textures/1.png",
		"assets/textures/Checkerboard.png",
		"assets/textures/Creed.jpg",
		"assets/textures/poop.png"
	};
	int index = 0;

	Leaf::Ref<Leaf::VertexArray> m_VArray;
	
	Leaf::Ref<Leaf::VertexArray> m_SquareVA;

	Leaf::ShaderManager m_ShaderMan;
	Leaf::Ref<Leaf::Texture> m_Texture;

	Leaf::OrthographicCameraController m_CameraController;

	glm::vec4 m_ColorA = glm::vec4(0.0f), m_ColorB = glm::vec4(1.0f);
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