#pragma once

#include "core.h"

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


