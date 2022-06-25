#pragma once

#include "Engine/LayerStack.h"
#include "Events/Event.h"
#include "Window.h"
#include "Events/ApplicationEvent.h"

namespace Engine {
	
	class EG_API Application
	{
	public:
		Application();
		virtual ~Application();

		void run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	};

	//定义在客户端中
	Application* CreateApplication();

}


