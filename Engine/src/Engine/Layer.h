#pragma once

#include "Engine/core.h"
#include "Engine/Events/Event.h"

namespace Engine {

	class EG_API Layer
	{
	public:
		Layer(const std::string& name = "JLayer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnImguiRender() {}
		virtual void OnEvent(Event& event){}

		inline const std::string& GetName()const {return m_DebugName;}
	protected:
		std::string m_DebugName;
	};

}
