#pragma once

#include "core.h"

#include "Engine/Core/LayerStack.h"
#include "Engine/Events/Event.h"
#include "Window.h"
#include "Engine/Events/ApplicationEvent.h"

#include "Engine/Core/TimeStep.h"

#include "Engine/Imgui/ImguiLayer.h"

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

		static inline Application& Get() {return *s_Instance;}//懒汉单例
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResized(WindowResizedEvent& e);
	private:
		std::unique_ptr<Window> m_Window;
		ImguiLayer* m_ImguiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LatsFrameTime = 0.0f;
	private:
		static Application* s_Instance;
	};

	//定义在客户端中
	Application* CreateApplication();

}


