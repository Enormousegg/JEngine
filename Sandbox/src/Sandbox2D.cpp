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

	{
		EG_PROFILE_SCOPE("Renderer Prop");

		Engine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Engine::RenderCommand::Clear();
	}

	{
		EG_PROFILE_SCOPE("Renderer Draw");

		Engine::Renderer2D::BeginScene(m_CameraController.GetCamera());
		Engine::Renderer2D::DrawRotateQuad({ -1.0f,0.0f }, { 0.8f, 0.8f }, glm::radians(45.0f), glm::vec4(0.8f, 0.2f, 0.3f, 1.0f));
		Engine::Renderer2D::DrawQuad({ 0.5f,-0.5f }, { 0.5f, 0.75f }, glm::vec4(0.2f, 0.3f, 0.8f, 1.0f));//为何此处无法用初始化列表进行初始化
		Engine::Renderer2D::DrawQuad({ 0.0f,0.0f,-0.1f }, { 10.0f, 10.0f }, m_Checkerboardtexture,10.0f);
		Engine::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImguiRender()
{
	EG_PROFILE_FUNCTION();

	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	
	ImGui::End();
}

void Sandbox2D::OnEvent(Engine::Event& e)
{
	m_CameraController.Onevent(e);
}
