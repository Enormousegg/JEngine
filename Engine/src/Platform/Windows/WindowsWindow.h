#pragma once

#include "Engine/Core/Window.h"
#include "Engine/Renderer/GraphicsContext.h"

#include "GLFW/glfw3.h"

namespace Engine {

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& pops);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth()const override { return m_Data.Width; }
		inline unsigned int GetHeight()const override { return m_Data.Height; }

		//��������
		inline void SetEventCallback(const EventCallbackFn& callback)override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool isVSync() const override;

		inline virtual void* GetNativeWindow() const { return m_Window; }
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
	private:
		GLFWwindow* m_Window;
		GraphicsContext* m_Context;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};

}