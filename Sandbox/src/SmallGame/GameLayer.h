#pragma once

#include "Engine.h"

#include "Level.h"
#include <Imgui/imgui.h>

class GameLayer : public Engine::Layer
{
public:
	GameLayer();
	virtual ~GameLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Engine::TimeStep ts) override;
	virtual void OnImguiRender() override;
	void OnEvent(Engine::Event& e) override;
	bool OnMouseButtonPressed(Engine::MouseButtonPressedEvent& e);
	bool OnWindowResize(Engine::WindowResizedEvent& e);
private:
	void CreateCamera(uint32_t width, uint32_t height);
private:
	Engine::Scope<Engine::OrthographicCamera> m_Camera;
	Level m_Level;
	ImFont* m_Font;
	float m_Time = 0.0f;
	bool m_Blink = false;

	enum class GameState
	{
		Play = 0, MainMenu = 1, GameOver = 2
	};

	GameState m_State = GameState::MainMenu;
};