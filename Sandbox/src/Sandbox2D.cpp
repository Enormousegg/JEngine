#include "Sandbox2D.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


Sandbox2D::Sandbox2D()
	:Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{
}

void Sandbox2D::OnAttach()
{
	EG_PROFILE_FUNCTION();

	m_Checkerboardtexture = Engine::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach()
{
	EG_PROFILE_FUNCTION();

}

void Sandbox2D::OnUpdate(Engine::TimeStep ts)
{
	EG_PROFILE_FUNCTION();

	//update
	m_CameraController.OnUpdate(ts);

	Engine::Renderer2D::ResetStats();
	{
		EG_PROFILE_SCOPE("Renderer Prop");

		Engine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Engine::RenderCommand::Clear();
	}

	{
		static float rotation = 0.0f;
		rotation += ts * 20.0f;

		EG_PROFILE_SCOPE("Renderer Draw");

		Engine::Renderer2D::BeginScene(m_CameraController.GetCamera());
		Engine::Renderer2D::DrawRotateQuad({ 1.0f,0.0f }, { 0.8f, 0.8f }, -45.0f, glm::vec4(0.8f, 0.2f, 0.3f, 1.0f));
		Engine::Renderer2D::DrawQuad({ -1.0f,0.0f }, { 0.8f, 0.8f }, glm::vec4(0.8f, 0.2f, 0.3f, 1.0f));
		Engine::Renderer2D::DrawQuad({ 0.5f,-0.5f }, { 0.5f, 0.75f }, glm::vec4(0.2f, 0.3f, 0.8f, 1.0f));//为何此处无法用初始化列表进行初始化
		Engine::Renderer2D::DrawQuad({ 0.0f,0.0f,-0.1f }, { 20.0f, 20.0f }, m_Checkerboardtexture, 10.0f);
		Engine::Renderer2D::DrawRotateQuad({ -2.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, rotation, m_Checkerboardtexture, 20.0f);
		Engine::Renderer2D::EndScene();

		Engine::Renderer2D::BeginScene(m_CameraController.GetCamera());
		for (float y = -5.0f; y < 5.0f; y += 0.1f)
		{
			for (float x = -5.0f; x < 5.0f; x += 0.1f)
			{
				glm::vec4 color = { (x + 5.0) / 10.0f, 0.4f, (y + 5.0) / 10.0f, 0.5f };
				Engine::Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
			}
		}
		Engine::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImguiRender()
{
	EG_PROFILE_FUNCTION();

	ImGui::Begin("Settings");

	auto stats = Engine::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	
	ImGui::End();
}

void Sandbox2D::OnEvent(Engine::Event& e)
{
	m_CameraController.Onevent(e);
}
