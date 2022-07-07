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

	//���ڴ��ڵ�����ϵͳ�ӿ�
	class EG_API Window
	{
	public:
		//����һ��void�����ĺ���ָ����󣬺�������δEvent������,usingָ������
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}//��������������֤����������������

		virtual void OnUpdate() = 0;//���麯��

		virtual unsigned int GetWidth()const = 0;
		virtual unsigned int GetHeight()const = 0;

		//��������
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;//�ص�����ָ������������Ϊ����
		virtual void SetVSync(bool enabled) = 0;//���ô�ֱͬ��
		virtual bool isVSync()const = 0;//�ж��Ƿ�ֱͬ��

		virtual void* GetNativeWindow() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());
	};
}