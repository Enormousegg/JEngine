#pragma once

#include "core.h"
#include "Events/Event.h"

namespace Engine {
	
	class EG_API Application
	{
	public:
		Application();
		virtual ~Application();

		void run();
	};

	//�����ڿͻ�����
	Application* CreateApplication();

}


