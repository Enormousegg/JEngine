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

		virtual void OnAttach()override;
		virtual void OnDetach()override;
		virtual void OnImguiRender()override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};

}