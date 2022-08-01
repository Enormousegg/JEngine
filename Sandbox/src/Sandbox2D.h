#pragma once

#include "Engine.h"

#include "ParticleSystem/ParticleSystem.h"

class Sandbox2D : public Engine::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach()override;
	virtual void OnDetach()override;

	void OnUpdate(Engine::TimeStep ts) override;
	virtual void OnImguiRender() override;
	void OnEvent(Engine::Event& e) override;
private:
	Engine::OrthographicCameraController m_CameraController;

	//temp
	Engine::Ref<Engine::VertexArray> m_SquareVA;
	Engine::Ref<Engine::Shader> m_FlatColorShader;

	Engine::Ref<Engine::Texture2D> m_Checkerboardtexture;
	Engine::Ref<Engine::Texture2D> m_SpriteSheet;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };

	ParticleSystem m_ParticleSystem;
	ParticleProps m_Particle;
};