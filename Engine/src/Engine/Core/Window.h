#pragma once

#include "egpch.h"

#include "Engine/Core/core.h"
#include "Engine/Events/Event.h"

namespace Engine {

	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "JEngine",
			unsigned int width = 1280,
			unsigned int height = 720)
			:Title(title), Width(width), Height(height){}
	};

	//基于窗口的桌面系统接口
	class EG_API Window
	{
	public:
		//定义一个void函数的函数指针对象，函数参数未Event的引用,using指定别名
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}//虚析构函数，保证派生类能正常析构

		virtual void OnUpdate() = 0;//纯虚函数

		virtual unsigned int GetWidth()const = 0;
		virtual unsigned int GetHeight()const = 0;

		//窗口属性
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;//回调函数指针对象的引用作为参数
		virtual void SetVSync(bool enabled) = 0;//设置垂直同步
		virtual bool isVSync()const = 0;//判断是否垂直同步

		virtual void* GetNativeWindow() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());
	};
}