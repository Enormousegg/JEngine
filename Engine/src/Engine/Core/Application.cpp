#include "egpch.h"
#include "Application.h"

#include "Engine/Core/Log.h"

#include "Engine/Renderer/Renderer.h"

#include "Engine/Core/Imput.h"

#include "GLFW/glfw3.h"

namespace Engine {

	Application* Application::s_Instance = nullptr;

	Application::Application() 
	{
		EG_CORE_ASSERT(!s_Instance,"Application already exists!")
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(EG_BIND_EVENT_FN(Application::OnEvent));
		//m_Window->SetVSync(false);

		Renderer::Init();

		m_ImguiLayer = new ImguiLayer();
		PushOverlay(m_ImguiLayer);
	}

	Application::~Application() 
	{
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(EG_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizedEvent>(EG_BIND_EVENT_FN(Application::OnWindowResized));

		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
		{
			if (e.m_Handled)
				break;
			(*it)->OnEvent(e);
		}
	}

	void Application::run()
	{
		while (m_Running)
		{
			float time = (float)glfwGetTime();
			TimeStep timestep = time - m_LatsFrameTime;
			m_LatsFrameTime = time;

			if (!m_Minimized)
			{
				for (Layer* layer : m_LayerStack)
					layer->OnUpdate(timestep);
			}

			m_ImguiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImguiRender();
			m_ImguiLayer->End();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResized(WindowResizedEvent& e)
	{
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());


		return false;
	}


}
