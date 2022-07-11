#include <Engine.h>
#include <Engine/Core/EntryPoint.h>

#include "imgui/imgui.h"

#include "Platform/OpenGL/OpenGLShader.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Sandbox2D.h"

class ExampleLayer : public Engine::Layer
{
public:
	ExampleLayer()
		:Layer("Example"),m_CameraController(1280.0f/720.0f)
	{
		m_VertexArray = Engine::VertexArray::Create();

		float vertices[3 * 7] = {
			-0.5f,-0.5f,0.0f, 1.0f,0.0f,1.0f,1.0f,
			 0.5f,-0.5f,0.0f, 1.0f,0.0f,1.0f,1.0f,
			 0.0f, 0.5f,0.0f, 1.0f,0.0f,1.0f,1.0f
		};

		Engine::Ref<Engine::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Engine::VertexBuffer::Create(vertices, sizeof(vertices)));
		Engine::BufferLayout layout = {
			{ Engine::ShaderDataType::Float3,"a_Position"},
			{ Engine::ShaderDataType::Float4,"a_Color"}
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);


		uint32_t indices[3] = { 0,1,2 };
		Engine::Ref<Engine::IndexBuffer> indexBuffer;
		indexBuffer.reset(Engine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);


		m_SquareVA = Engine::VertexArray::Create();

		float squareVertices[4 * 5] = {
			-0.5f,-0.5f,0.0f,0.0f,0.0f,
			 0.5f,-0.5f,0.0f,1.0f,0.0f,
			 0.5f, 0.5f,0.0f,1.0f,1.0f,
			-0.5f, 0.5f,0.0f,0.0f,1.0f
		};

		Engine::Ref<Engine::VertexBuffer> squareVB;
		squareVB.reset(Engine::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ Engine::ShaderDataType::Float3,"a_Position"},
			{ Engine::ShaderDataType::Float2,"a_TexCoord"}
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0,1,2,2,3,0 };
		Engine::Ref<Engine::IndexBuffer> squareIB;
		squareIB.reset(Engine::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);


		std::string VertexSrc = R"(
			#version 330 core
			
			layout(location=0) in vec3 a_Position;
			layout(location=1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;
			
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position,1.0);
			}
		)";

		std::string FragmentSrc = R"(
			#version 330 core

			in vec3 v_Position;
			in vec4 v_Color;
			
			layout(location=0) out vec4 color;
			
			void main()
			{
				color = vec4(v_Position*0.5+0.5, 1.0);
			}
		)";

		m_Shader = Engine::Shader::Create("VertexPosColor",VertexSrc, FragmentSrc);

		std::string FlatColorVertexSrc = R"(
			#version 330 core
			
			layout(location=0) in vec3 a_Position;
			//layout(location=1) in vec2 a_TexCoord;


			uniform mat4 u_Transform;
			uniform mat4 u_ViewProjection;
			
			void main()
			{
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position,1.0);
			}
		)";

		std::string FlatColorFragmentSrc = R"(
			#version 330 core
			
			layout(location=0) out vec4 color;

			uniform vec3 v_Color;
			
			void main()
			{
				//color = vec4(0.2, 0.3, 0.8, 1.0);
				color = vec4(v_Color,1.0f);
			}
		)";
		m_FlatColorShader = Engine::Shader::Create("FlatColor", FlatColorVertexSrc, FlatColorFragmentSrc);

		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

		m_Texture = (Engine::Texture2D::Create("assets/textures/Checkerboard.png"));
		m_LogoTexture = (Engine::Texture2D::Create("assets/textures/Logo.png"));

		std::dynamic_pointer_cast<Engine::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<Engine::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(Engine::TimeStep ts) override
	{
		//update
		m_CameraController.OnUpdate(ts);

		Engine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Engine::RenderCommand::Clear();

		Engine::Renderer::BeginScene(m_CameraController.GetCamera());

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Engine::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Engine::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("v_Color", m_SquareColor);


		for (int y = 0; y < 20; ++y)
		{
			for (int x = 0; x < 20; ++x)
			{
				glm::vec3 pos(x * 0.11, y * 0.11, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Engine::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}

		auto textureShader = m_ShaderLibrary.Get("Texture");

		m_Texture->Bind();
		Engine::Renderer::Submit(textureShader, m_SquareVA,glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		m_LogoTexture->Bind();
		Engine::Renderer::Submit(textureShader, m_SquareVA,glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		//三角形
		//Engine::Renderer::Submit(m_Shader, m_VertexArray);

		Engine::Renderer::EndScene();
	}

	virtual void OnImguiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(Engine::Event& e) override
	{
		m_CameraController.Onevent(e);

		//if (e.GetEventType() == Engine::EventType::WindowResize)
		//{
		//	auto re = (Engine::WindowResizedEvent&)e;//变量向子类转换

		//	float zoom = (float)re.GetWidth() / 1280.f;
			//m_CameraController.SetZoomLevel(zoom);
		//}
	}
private:
	Engine::ShaderLibrary m_ShaderLibrary;
	Engine::Ref<Engine::Shader> m_Shader;
	Engine::Ref<Engine::VertexArray> m_VertexArray;

	Engine::Ref<Engine::Shader> m_FlatColorShader;
	Engine::Ref<Engine::VertexArray> m_SquareVA;

	Engine::Ref<Engine::Texture2D> m_Texture,m_LogoTexture;

	Engine::OrthographicCameraController m_CameraController;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};

class Sandbox :public Engine::Application
{
public:
	Sandbox()
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}

	~Sandbox()
	{

	}
};



Engine::Application* Engine::CreateApplication()
{
	return new Sandbox();
}