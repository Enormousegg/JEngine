#pragma once

#include "Engine/Layer.h"
#include "Engine/Events/MouseEvent.h"
#include "Engine/Events/ApplicationEvent.h"
#include "Engine/Events/KeyEvent.h"

namespace Engine {

	class EG_API ImguiLayer : public Layer
	{
	public:
		ImguiLayer();
		~ImguiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate();

	private:
		float m_Time = 0.0f;
	};

}